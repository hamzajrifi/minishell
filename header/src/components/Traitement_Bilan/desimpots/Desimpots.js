import React, { useState , useEffect } from 'react';
import CompanyContext from "../../../context/EntreprisesContext";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faFileCirclePlus, faTrashCan, faUserPlus
} from "@fortawesome/free-solid-svg-icons";
import NewDesimpots from './NewDesimpots';

const ListDesimpots =({getCompanyId, allwedForm})=>{
	const [companies, setCompanies] = useState([]);
	const [filtersearch, setfiltersearch] = useState("Raisonsocial");

    var retnbr = 0;
	
	const getCompanies = async () => {
		const data = await CompanyContext.getAllcompanies();
		  setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
	};
	const [datasearch, setsearch] = useState("");
	
	// function check id 
	
	const deleteHandler = async (id) => {
		const newTva = {
			BilanDesimpots:{},
		};
		await CompanyContext.updatecompany(id, newTva);
		getCompanies();
	};
	const updatehandler = (e) => {
		getCompanyId(e.id);
		allwedForm();
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
	  };
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
                   Nouvelle Decalaration De Bilan des impots
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
            				<th className='text-center'>Bilan HT</th>
            				<th className='text-center'>Bilan TTC</th>
            				<th className='text-center'>Reste HC</th>
                            <th className='text-center' >Reste TTC</th>
							<th></th>
							<th></th>
            			</tr>
                          </thead>
                          <tbody>
            		{ retnbr =   companies.filter((com) =>
			        	((checkfilter(com).toLowerCase().includes(datasearch)
			        	|| checkfilter(com).toUpperCase().includes(datasearch) 
              			|| checkfilter(com).includes(datasearch) )
						&& com.BilanDesimpots !== undefined
						&& (Object.keys(com.BilanDesimpots).length > 0)
						&& (com.BilanDesimpots) !== undefined 
						))
            			.map( (com , index)=> {
            				return (
            					<tr key={com.id}>
									<td className='text-center'> {index + 1} </td>
									<td > <h5>{com.Raisonsocial}</h5> </td>
									<td > <h6>{com.Responsable}</h6> </td>
									<td className='text-center'> <h6>{com.BilanDesimpots.ht} Dh</h6> </td>
									<td className='text-center'> <h6>{com.BilanDesimpots.ttc} Dh</h6> </td>
									<td className='text-center'> <h6>{com.BilanDesimpots.resteht} Dh</h6> </td>
									<td className='text-center'> <h6>{com.BilanDesimpots.restettc} Dh</h6> </td>
                                	{/* <td className='text-center'>
            						    <h4>
                                	        {com.TVA[com.TVA.length - 1].termineMois ?
                                	         <FontAwesomeIcon icon = {faCheckDouble} className="text-success bi "/>
                                	         :<FontAwesomeIcon icon = {faXmark} className="text-danger" />}
                                	    </h4>
            						</td> */}
            						<td className=" text-center">
            						  <button 
            							  className="btn btn-warning m-0 p-2"
            							  onClick={(e)=> updatehandler(com)}
            						  >
            							  Ajouter un paiement
										  <FontAwesomeIcon icon = {faFileCirclePlus} className="ml-1"/>
            						  </button>
            						</td>
									<td className=" text-center">
                                        {/* <!-- Button trigger modal --> */}
                                            <button type="button" className="btn btn-scend mr-0 p-2" 
                                                   data-toggle="modal" data-target={"#" + com.id + "modelSupp"}
												   >
                                                Supprimer
                                                <FontAwesomeIcon icon = {faTrashCan} className="ml-1"/>
                                            </button>

                                            {/* <!-- Modal --> */}
                                            <div className="modal fade" id={com.id + "modelSupp"} tabIndex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="false">
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
}

export default function Desimpots() {
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
        {showForm ?  <NewDesimpots hideForm={hideForm} Id={companyId}/> : <ListDesimpots getCompanyId={getCompanyeIdHandler} allwedForm={allwedForm} />}
    </div>
  )
}
