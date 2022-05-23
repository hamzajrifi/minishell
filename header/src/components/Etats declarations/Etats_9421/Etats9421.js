import { faTrashCan, faUserPlus } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React, { useEffect, useState } from 'react'
import CompanyContext  from '../../../context/EntreprisesContext';
import NewEtats9421 from './NewEtats9421';

const ListEatas9421 =({allwedForm}) => {
	const [datasearch, setsearch] = useState("");
	const [companies, setCompanies] = useState([]);
  const [filtersearch, setfiltersearch] = useState("Raisonsocial");

    var retnbr = 0;

    const getCompanies = async () => {
		const data = await CompanyContext.getAllcompanies();
		setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
	};
  /// function check id 
	const deleteHandler = async (id) => {
		const newService = {
			Etats9421:{},
		};
		await CompanyContext.updatecompany(id, newService);
		getCompanies();
	};
    const checkallwedForm = () => {
		allwedForm();
	};
  const checkfilter = (e) => {
    if(filtersearch === "Raisonsocial")
      return e.Raisonsocial;
    else if (filtersearch === "Responsable")
      return e.Responsable;
  }
	useEffect(() => {
		getCompanies();
	}, []);

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
                                   Nouvelle Etats9421
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
                                </select>
                            </div>
                             <div  className="row">
                                <div  className="col-12">
                                    <div  className="table-responsive">
                                        <table className="display expandable-table table-striped" style={{width:"100%"}}>
                                            <thead>
				            		            <tr>
            	            		            	<th></th>
            	            		            	<th>Raisonsocial</th>
            	            		            	<th>Responsable</th>
            	            		            	<th>Effectue</th>
                                            <th>Type Service</th>
                                                    <th></th>
            	            		            </tr>
                                            </thead>
                                            <tbody>
            	            	                { retnbr = companies.filter((com) =>
			        	                                  ((checkfilter(com).toLowerCase().includes(datasearch)
			        	                                  || checkfilter(com).toUpperCase().includes(datasearch) 
              	                                 	|| checkfilter(com).includes(datasearch)) )
            		                                   && com.Etats9421 !== undefined 
            			                            && (Object.keys(com.Etats9421).length > 0)).map( (com , index)=> {
                                                       return (
                                                            <tr key={com.id}>
            				  	                                <td>{index + 1}</td>
            					                                  <td><h5>{com.Raisonsocial}</h5></td>
            					                                  <td><h6>{com.Responsable}</h6></td>
            					                                  <td><h6>{com.Etats9421.ht}</h6></td>
            					                                  <td><h6>{com.Etats9421.typeService}</h6></td>
                                                        <td>
                                        {/* <!-- Button trigger modal --> */}
                                            <button type="button" className="btn btn-scend m-0 p-2" 
                                                   data-toggle="modal" data-target={"#" + com.id + "modelSuppEtat"}
                                                   >
                                                Supprimer
                                                <FontAwesomeIcon icon = {faTrashCan} className="ml-1"/>
                                            </button>

                                            {/* <!-- Modal --> */}
                                            <div className="modal fade" id={com.id + "modelSuppEtat"} tabIndex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="false">
                                              <div className="modal-dialog" role="document">
                                                <div className="modal-content">

                                                  <div className="modal-body  mb-0">
                                                    <h3>Êtes-vous sûr de vouloir supprimer cette service de<strong> {com.Raisonsocial} </strong>...</h3>
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
                                                      </tr>
            				                                	);
							                                      })} 
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

const Etats9421 =()=> {
    const [showForm, setForm] = useState(false);
    const allwedForm = () => setForm (true);
    const hideForm = () => setForm (false);
  return (
    <>
    {}
        {showForm ?  <NewEtats9421 hideForm={hideForm}  /> : <ListEatas9421 allwedForm={allwedForm} />}
    </>
  )
}
export default Etats9421;
