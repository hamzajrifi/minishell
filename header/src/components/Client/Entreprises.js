import { faFilePen, faTrashCan, faUserPlus } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React, { useState , useEffect } from 'react';
import CompanyContext from "../../context/EntreprisesContext";
import NewClinet from "./NewClinet";

const CompaniensList = ({getCompnyId, allwedForm})=> {
	const [companies, setCompanies] = useState([]);
	const [datasearch, setsearch] = useState("");
	const [filtersearch, setfiltersearch] = useState("Raisonsocial");
	var retnbr = 0;
	useEffect (() => {
		getCompanies();
	},[]);
    const getCompanies = async () => {
      const data = await CompanyContext.getAllcompanies();
      setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
    };
  const checkallwedForm = () => {
    getCompnyId("");
    allwedForm();
  }
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
	const deleteHandler = async(id) => {
		await CompanyContext.deletecompany(id);
		getCompanies();
	};
	return (
	<>
  <div  className="row">
            <div  className="col-md-12 grid-margin stretch-card">
              <div  className="card">
                <div  className="card-body">
                <div className='m-2'>
                <button 
                    className="btn btn-info m-2 mr-4"
                    onClick={checkallwedForm}
                  >
                     <FontAwesomeIcon icon = {faUserPlus} className ='text-white icon-font-menu'/>
                    Ajouter une nouvelle entreprise
                </button>
                <button type='button'
                    className="btn btn btn-dark btn-rounded btn-icon"
                    onClick={getCompanies}
                >
                  <i className="ti-reload btn-icon-prepend "></i>
                </button>
            </div>
                <div className="input-group mb-2">
                    <input  type="text" 
                            className="form-control"
                            placeholder="Search now"
                            aria-label="search"
                            aria-describedby="search" 
                            onChange = {(e) => setsearch(e.target.value)}
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
                  <div  className="row">
                    <div  className="col-12">
                      <div  className="table-responsive">
                        <table className="display expandable-table table-striped" style={{width:"100%"}}>
                          <thead>
                            <tr>
                              <th>#</th>
                              <th>Raison social</th>
                              <th>Date de ngagement</th>
                              <th>Origine de fonds</th>
                              <th>Tribunal</th>
                              <th>Address</th>
                              <th>Responsable</th>
                              <th></th>
                              <th></th>
                              <th></th>
                            </tr>
                          </thead>
                          <tbody>
							  
                          {retnbr = companies.filter((com) =>
			                    (checkfilter(com).toLowerCase().includes(datasearch)
			                    || checkfilter(com).toUpperCase().includes(datasearch) 
                          || checkfilter(com).includes(datasearch) 
                        	)).map( (com , index)=>  {
								        return (
								          <tr key={com.id}>
							                      <td>
                                                {index + 1}
                                              </td>
                                              <td>
                                                {com.Raisonsocial}
                                              </td>
                                              <td>
                                                {com.Datedengagement}
                                              </td>
                                              <td>
                                                    {com.Originedefonds}
                                                  </td>
                                              <td>
                                                    {com.Tribunal}
                                                  </td>
                                              <td>
                                                    {com.Address}
                                                  </td>
                                              <td>
                                                {com.Responsable}
                                              </td>
                                              <td>
                                                <button 
                                                    className="btn btn-warning m-0 p-1"
                                                    onClick={(e)=> getCompnyId(com.id)}
                                                >
                                                    Modifier
                                                    <FontAwesomeIcon icon = {faFilePen} className="ml-1"/>
                                                </button>
                                              </td>
                                              <td>
                                                {/* <!-- Button trigger modal --> */}
                                                    <button type="button" className="btn btn-scend m-0 p-2" 
                                                           data-toggle="modal" data-target="#exampleModal">
                                                        Supprimer
                                                        <FontAwesomeIcon icon = {faTrashCan} className="ml-1"/>
                                                    </button>
                                              
                                                    {/* <!-- Modal --> */}
                                                    <div className="modal fade" id="exampleModal" tabIndex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="false">
                                                      <div className="modal-dialog" role="document">
                                                        <div className="modal-content">

                                                          <div className="modal-body  mb-0">
                                                            <h3>Êtes-vous sûr de vouloir supprimer cette entreprise...</h3>
                                                          </div>
                                                          <div className="modal-footer p-1">
                                                            <button type="button" className="btn btn-secondary mr-2" data-dismiss="modal">Close</button>
                                                            <button 
                                                                  className="btn btn-scend mr-2 p-3"
                                                                  onClick={(e) =>  deleteHandler(com.id)}
                                                                  data-dismiss="modal"
                                                              >
                                                                  Supprimer
                                                                  <FontAwesomeIcon icon = {faTrashCan} className="ml-1"/>
                                                            </button>
                                                          </div>
                                                        </div>
                                                      </div>
                                                    </div>
                                                </td>
                                              <td>
                                                <button 
                                                    className="btn btn-primary m-0 p-1"
                                                  >
                                                    plus
                                                </button>
                                              </td>
                                           </tr>
                                    );})
									}
                          </tbody>
                      </table>
									{!(Array.isArray(retnbr) && retnbr.length) ? 
										<div className="text-center mt-2">aucune donnée disponible</div>
									: null}
                      </div>
                    </div>
                  </div>
                  </div>
                </div>
              </div>
            </div>
            </>
	)
}

// Entreprises List
function Entreprises({datainfoUser}){
	  const [companyId, setCompnyId] = useState("");
  	const [showForm, setShowForm] = useState(false);
  	const allwedForm = () => setShowForm(true);
  	const hideForm = () => setShowForm(false);

  	const getcompanyIdHandler = (id) => {
  	  allwedForm();
  	  setCompnyId(id);
  	};
	return (
		<div>
			{ showForm ? <NewClinet id= {companyId} setCompanyId={setCompnyId} hideForm={hideForm} datainfoUser={datainfoUser}/> : null }
			<div className= {showForm ? "ProspectsList" : ""}>
			<CompaniensList getCompnyId={getcompanyIdHandler} allwedForm={allwedForm}/>
			</div>
		</div>
	)
}
export default Entreprises;