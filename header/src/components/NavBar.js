import React, { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import { signOut } from "firebase/auth";
import { useNavigate } from "react-router-dom";
import { auth } from "../firebase/firebase-config";
import CompanyContext from "../context/EntreprisesContext";

const Navbar =({infoUser, Uid, AdminUid})=> {
  const navigate = useNavigate();
	const [filtersearch, setfiltersearch] = useState("Raisonsocial");
	const [hidelistsearch , setHidelistsearch] = useState(false);
	const [datasearch, setsearch] = useState("");
	const [companies, setCompanies] = useState([]);
  
 // function allow list search
 const inputsearch =(e)=>{
  setHidelistsearch(false);
  setsearch(e);
};

 // function get data companies
 const getCompanies = async () => {
  const data = await CompanyContext.getAllcompanies();
  setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
};

// function check filter
const checkfilter = (e) => {
  if(filtersearch === "Raisonsocial")
    return e.Raisonsocial;
  else if (filtersearch === "Responsable")
    return e.Responsable;
  else if (filtersearch === "Tribunal")
    return e.Tribunal;
  else if (filtersearch === "Originedefonds")
    return e.Originedefonds;
}
// function logout
  const logOut = async () => {
    try {
      await signOut(auth);
      navigate("/");
    } catch (err) {
      alert("pour certaines raisons, nous ne pouvons pas nous connecter");
    }
  };
  // function after choise company
  const Choisecompany =(e)=>{
    setsearch("");
    setHidelistsearch(true);
  }
  // use Effect
  useEffect (() => {
    getCompanies();
  },[]);
  return (
         <nav className="navbar col-lg-12 col-12 p-0 fixed-top d-flex flex-row">
      <div className="text-center navbar-brand-wrapper d-flex align-items-center justify-content-center">
        <Link className="navbar-brand brand-logo mr-5" to="/"><img src="images/logo-nav.png" className="mr-2" alt="logo"/></Link>
        <Link className="navbar-brand brand-logo-mini" to="/"><img src="images/logo-nav-mini.png" alt="logo"/></Link>
      </div>
      <div className="navbar-menu-wrapper d-flex align-items-center justify-content-end">
        <button className="navbar-toggler navbar-toggler align-self-center " type="button" data-toggle="minimize">
          <span className="icon-menu"></span>
        </button>
        <div className="col-lg-11 row ">
              <div className="input-group">
                  <input  type="text" 
                    className="orm-outline w-75 p-2 ml-3"
                    placeholder="Search now"
                    aria-label="search"
                    aria-describedby="search"
						        value={datasearch}
                    onChange = {(e) => inputsearch(e.target.value)}
                      />
			    	        <select className=" btn-secondary p-0 form-select" 
                        value={filtersearch}
			    	        	  onChange = {(e) => setfiltersearch(e.target.value)}
                        >
                    	<option value="Raisonsocial">Raison social</option>
                    	<option value="Responsable">Responsable</option>
                    	<option value="Tribunal">Tribunal</option>
                    	<option value="Originedefonds">Origine de fonds</option>
                    </select>
              </div>
              <ul className="list-search w-75 position-absolute mt-5">
              
                  {datasearch === "" || hidelistsearch ? null
                  	: companies.filter((com) =>
			        (checkfilter(com).toLowerCase().includes(datasearch)
			        || checkfilter(com).toUpperCase().includes(datasearch) 
              		|| checkfilter(com).includes(datasearch) 
                  	)).map( (com , index)=>  {
                  return (
                        <Link className='list-group-item' 
                              onClick={()=>Choisecompany(com)} 
                              key={index + 1} to="/CheckDeposit" 
                              state={{com: com}}
                              >
                                {checkfilter(com)}
                        </Link>
              );
              })}
            </ul>
        </div>
        <ul className="navbar-nav navbar-nav-right">
          <li className="nav-item dropdown">
            <Link className="nav-link count-indicator dropdown-toggle" id="notificationDropdown" to="/" data-toggle="dropdown">
              <i className="icon-bell mx-0"></i>
              <span className="count"></span>
            </Link>
            <div className="dropdown-menu dropdown-menu-right navbar-dropdown preview-list" aria-labelledby="notificationDropdown">
              <p className="mb-0 font-weight-normal float-left dropdown-header">Notifications</p>
              <Link className="dropdown-item preview-item" to="/" >
                <div className="preview-thumbnail">
                  <div className="preview-icon bg-success">
                    <i className="ti-info-alt mx-0"></i>
                  </div>
                </div>
                <div className="preview-item-content">
                  <h6 className="preview-subject font-weight-normal">Application Error</h6>
                  <p className="font-weight-light small-text mb-0 text-muted">
                    Just now
                  </p>
                </div>
              </Link>
              <Link className="dropdown-item preview-item" to="/">
                <div className="preview-thumbnail">
                  <div className="preview-icon bg-warning">
                    <i className="ti-settings mx-0"></i>
                  </div>
                </div>
                <div className="preview-item-content">
                  <h6 className="preview-subject font-weight-normal">Settings</h6>
                  <p className="font-weight-light small-text mb-0 text-muted">
                    Private message
                  </p>
                </div>
              </Link>
              <Link className="dropdown-item preview-item" to="/">
                <div className="preview-thumbnail">
                  <div className="preview-icon bg-info">
                    <i className="ti-user mx-0"></i>
                  </div>
                </div>
                <div className="preview-item-content">
                  <h6 className="preview-subject font-weight-normal">New user registration</h6>
                  <p className="font-weight-light small-text mb-0 text-muted">
                    2 days ago
                  </p>
                </div>
              </Link>
            </div>
          </li>
          <li className="nav-item nav-profile dropdown">
            <div className="nav-link dropdown-toggle"  data-toggle="dropdown" id="profileDropdown">
              <img src="images/user-image.png" alt="profile"/><h5 className="d-inline">{infoUser.name}</h5>
            </div>
            <div className="dropdown-menu dropdown-menu-right navbar-dropdown" aria-labelledby="profileDropdown">
              <Link className="dropdown-item" to="/Profile">
                <i className="ti-user text-primary"></i>
                Profile
              </Link>
              {!infoUser || (Uid !== AdminUid) ? null :
              <Link className="dropdown-item" to="/Admin">
                <i className="ti-settings text-primary"></i>
                Paramètre
              </Link>
              }
              <Link className="dropdown-item" to="" onClick={logOut}>
                <i className="ti-power-off text-primary"></i>
                Se déconnecter
              </Link>
            </div>
          </li>
        </ul>
        <button className="navbar-toggler navbar-toggler-right d-lg-none align-self-center" type="button" data-toggle="offcanvas">
          <span className="icon-menu"></span>
        </button>
      </div>
    </nav>
  );
}
export default Navbar;
