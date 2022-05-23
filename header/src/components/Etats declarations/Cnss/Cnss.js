import { faCheckDouble, faFileCirclePlus, faTrashCan, faUserPlus, faXmark } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React, { useEffect, useState } from 'react'
import { Link } from 'react-router-dom';
import  CompanyContext  from '../../../context/EntreprisesContext';
import NewCnss from './NewCnss';

const ListCnss = ({getCompanyId, allwedForm}) =>{
        const [companies, setCompanies] = useState([]);
        const [filtersearch, setfiltersearch] = useState("Raisonsocial");
        var retnbr = 0;
        
        const getCompanies = async () => {
            const data = await CompanyContext.getAllcompanies();
              setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
        };
        const [datasearch, setsearch] = useState("");
        
        const deleteHandler = async (id) => {
            const newService = {
                CNSS:{},
            };
            await CompanyContext.updatecompany(id, newService);
            getCompanies();
        };
    
        const checkallwedForm = () => {
            getCompanyId("");
            allwedForm();
          };
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
        useEffect(() => {
            getCompanies();
        }, []);
    
        return (
            <>
             <div  className="row">
                <div  className="col-md-12 grid-margin stretch-card">
                  <div  className="card">
                    <div  className="card-body pt-0">
                    <div className='m-2'>
                    <button 
                        className="btn btn-info m-2 mr-4"
                        onClick={checkallwedForm}
                      >
                         <FontAwesomeIcon icon = {faUserPlus} className ='text-white icon-font-menu'/>
                       Nouvelle Decalaration De Cnss
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
            				<th>Raisonsocial</th>
            				<th>Responsable</th>
            				<th>CNSS HT</th>
            				<th>CNSS TTC</th>
            				<th>Totale </th>
                    <th>Reste </th>
                    <th>Deposit</th>
							<th>Totale Annuelle TTC</th>
            				<th>Paid</th>
							<th></th>
							<th></th>
            			</tr>
              </thead>
              <tbody>
            		{ retnbr =   companies.filter((com) =>
			        	((checkfilter(com).toLowerCase().includes(datasearch)
			        	|| checkfilter(com).toUpperCase().includes(datasearch) 
              	|| checkfilter(com).includes(datasearch) )
						    && com.CNSS !== undefined
            			&& (Object.keys(com.CNSS).length > 0)))
            			.map( (com , index)=> {
            				return (
            					<tr key={com.id}>
            				  		<td>
            						  {index + 1}
            						</td>
            						<td>
            							<h5>{com.Raisonsocial}</h5>
            						</td>
            						<td>
            						  <h6>{com.Responsable}</h6>
            						</td>
            						<td>
            							<h6>{com.CNSS.PriceMonthHt} Dh</h6>
            						</td>
            						<td>
										      <h6>{com.CNSS.PriceMonthTtc} Dh</h6>
            						</td>
            						<td>
            						   <h6>{com.CNSS.TotalResteNew} Dh</h6>
            						</td>
									      <td>
            						  <h6>{com.CNSS.ResteNew} Dh</h6>
            						</td>
								      	<td>
            						  <h6>No Deposit</h6>
            						</td>
            						<td>
            						  <h6>{com.CNSS.AnnuelleTtc} Dh</h6>
            						</td>
                                	<td>
            						    <h4>
                                {com.CNSS.ResteNew <= 0 ?
                                 <FontAwesomeIcon icon = {faCheckDouble} className="text-success bi "/>
                                 :<FontAwesomeIcon icon = {faXmark} className="text-danger" />}
                                	    </h4>
            						</td>
            						<td>
										<Link 	className='btn btn-warning m-0 p-2'
												to="/CheckDeposit" 
                              				state={{com: com}}
                              			>
											Deposit CNSS
										  <FontAwesomeIcon icon = {faFileCirclePlus} className="ml-1"/>
                        				</Link>
            						  
            						</td>
									<td>
                     {/* <!-- Button trigger modal --> */}
                         <button type="button" className="btn btn-scend mr-0 p-2" 
                              data-toggle="modal" data-target={"#" + com.id + "CNSSmodelSupp"}
											   >
                      Supprimer
                           <FontAwesomeIcon icon = {faTrashCan} className="ml-1"/>
                       </button>

                       {/* <!-- Modal --> */}
                       <div className="modal fade" id={com.id + "CNSSmodelSupp"} tabIndex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="false">
                         <div className="modal-dialog" role="document">
                           <div className="modal-content">

                             <div className="modal-body  mb-0">
                               <h3>Êtes-vous sûr de vouloir supprimer touts declaratios cette<strong> {com.Raisonsocial} </strong>entreprise...</h3>
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
    };



export default function Cnss() {
    const [showForm, setForm] = useState(false);
	const [companyId, setcompanyId] = useState("");
    const allwedForm = () => setForm (true);
    const hideForm = () => setForm (false);
    const getCompanyeIdHandler = (id) => {
		allwedForm();
		setcompanyId(id);
	};
  return (
    <div>	
        {showForm ?  <NewCnss hideForm={hideForm} id={companyId} /> : <ListCnss getCompanyId={getCompanyeIdHandler} allwedForm={allwedForm} />}
    </div>
  )
}
