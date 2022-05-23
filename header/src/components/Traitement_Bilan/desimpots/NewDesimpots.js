import { faMinus, faPlus } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React, { useEffect, useState } from 'react';
import  CompanyContext  from '../../../context/EntreprisesContext';
import NewClinet from '../../Client/NewClinet';


const  NewDesimpots = ({hideForm ,Id}) => {
  const [companies, setCompanies] = useState([]);
  const [filtersearch, setfiltersearch] = useState("Raisonsocial");
  const [datasearch, setsearch] = useState("");
  const [hidelistsearch, setHidelistsearch] = useState(false);
  const [idCompany, setIdCompany] = useState("");
  const [Prospects, setProspects] = useState([]);

  ///// variable declaration
	var tabCom = [];
  ////
  /// function get data company 
  const getCompanies = async () => {
    const data = await CompanyContext.getAllcompanies();
	const dataPr = await CompanyContext.getAllprospects();
    setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})));
	tabCom.push(companies);
    setProspects(dataPr.docs.map((doc)=> ({...doc.data(), id: doc.id})));
	tabCom.push(Prospects);
  };
  ////
  
  /// function check filter serch company 
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
  ////

  //// function after choise company
  const Choisecompany =(e) =>{
	setsearch(e.Raisonsocial);
	setIdCompany(e.id);
	setHidelistsearch(true);
}
  ////
  //// function handel submit 
  const handelSubmit = async  (e) => {
  
}
  ////

  /// function input search 
  const inputsearch =(e)=>{
	setHidelistsearch(false);
	setsearch(e);
  };
  ////

  //// use Effect 
  useEffect (() => {
    getCompanies();
  },[]);
  ////
  return (
	<div className="card p-0">
		<div className="card-body p-0">
			<h1 className=" text-center pb-2" >Ajouter un nouveau Bilan des impots</h1>
			<ul className="nav nav-pills mb-3 " id="Bilan-tab" role="tablist">
			  <li className="nav-item">
					<a className="nav-link active  btn-rounded btn p-2" 
					id="Bilan-cancel-tab"
					 data-toggle="pill" 
					 href="#Bilan-cancel" 
					 role="tab" 
					 aria-controls="Bilan-cancel" 
					aria-selected="true">
						<FontAwesomeIcon icon={faMinus}/>
					</a>
			  </li>
			  <li className="nav-item">
				   <a className="nav-link btn-rounded btn p-2" 
					  d="is-new-client-home-tab" 
					  data-toggle="pill" 
					  href="#Bilon-new-client" 
					  role="tab" 
					  aria-controls="Bilon-new-client" 
					  aria-selected="false">
						<FontAwesomeIcon icon={faPlus}/>

					</a>
			  </li>
		  </ul>
				<div className="tab-content p-0" id="Bilan-tabContent">
						<div className="tab-pane fade show active" id="Bilan-cancel" role="tabpanel" aria-labelledby="Bilan-cancel-tab">
							<div>
							  <div className="input-group ">
								<input  type="text" 
										className="form-control"
										placeholder="Search now"
										aria-label="search"
										aria-describedby="search"
										value={datasearch}
										onChange = {(e) => inputsearch(e.target.value)}
								/>
								<select className=" btn-secondary btn  p-0 btn-secondary form-select" 
											  value={filtersearch}
											  onChange = {(e) => setfiltersearch(e.target.value)}
										  >
											<option value="Raisonsocial">Raison social</option>
											<option value="Responsable">Responsable</option>
											<option value="Tribunal">Tribunal</option>
											<option value="Originedefonds">Origine de fonds</option>
									  </select>
							  </div>
							  <ul className="list-search">
								  {console.log(tabCom)}
							  {datasearch === "" || hidelistsearch ? null
							  : tabCom.filter((com)  =>
							  (checkfilter(com).toLowerCase().includes(datasearch)
							  || checkfilter(com).toUpperCase().includes(datasearch) 
								  || checkfilter(com).includes(datasearch) 
									)).map( (com , index)=>  {
								  return (
									<li  className='list-group-item' key={index + 1}
									  onClick={ () => Choisecompany(com)}>
										{com.Raisonsocial}
									</li>
							  );
								})}
							  </ul>
							</div>
							<form onSubmit={handelSubmit} className="pt-4">
							</form>
							<div className="">
								<button className="btn button-right btn-inverse-dark mr-2" onClick={hideForm}>Cancel</button>
							</div>
       			   		</div>
							  <div className="tab-pane fade show " id="Bilon-new-client" role="tabpanel" aria-labelledby="is-new-client-home-tab">
       			   				<NewClinet />
       			   		</div>
       			</div>
		
		</div>
		
	</div>
		    )
}
export default NewDesimpots;