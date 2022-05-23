import { faFilePen } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import React, { useEffect, useState } from 'react'
import { useLocation } from 'react-router-dom'
import  CompanyContext  from '../../context/EntreprisesContext';

export default function CheckDeposit() {
	const com = useLocation().state.com;
	const TVA = useLocation().state.com.TVA;
	const CNSS = useLocation().state.com.CNSS;
	const [message, setMessage] = useState ({error : false, msg: ""});
	
	
	/// function check Deposit TVA
	const checkDepositTva = async (v , e, i)=>{

		TVA.TVA[i].Deposit = v;
		const updateDeposit = {
			TVA : TVA,
		}
		try {
			if (e.id !== undefined && e.id !== "")
			{ 
			  await CompanyContext.updatecompany(e.id , updateDeposit);
			  setMessage({error : false, msg : "Update Deposit TVA succès!" });
			}
			}catch (err)
			{
			  setMessage({error : true, msg : err.message});
			}
	}
	/////
	/// functi check Deposit CNSS
	const checkDepositCnss = async (v, e, i)=> {
		CNSS.CNSS[i].Deposit = v;
		const updateDeposit = {
			CNSS : CNSS,
		}
		try {
			if (e.id !== undefined && e.id !== "")
			{ 
			  await CompanyContext.updatecompany(e.id , updateDeposit);
			  setMessage({error : false, msg : "Update Deposit CNSS succès!" });
			}
			}catch (err)
			{
			  setMessage({error : true, msg : err.message});
			}
	}
	////
	/////
	useEffect (() => {
		// console.log("loc" , com);
	}, [com, TVA]);
  return (
	  		<div>
			  	{message.msg && 
      			(
				  	<div class="alert bg-success text-white mt-0" role="alert">
						<div 
      			  			className={message.error ? "erroremessage" : "successmessage"}
      			    		variant = {message.error ? "danger" : "success"}
      			    		dismissible = "false"
      			    		onClose = {() => setMessage("")}
      						>{ message.msg}
						</div>
					</div>
				  )}
		 		 <div className='row'>
				  <div className="col-md-4 grid-margin stretch-card"  style={{ minWidth: "400px" }}>
					<div className="card">
						<div className="card-body text-center">
							<div className="row m-auto ">
        			            <div className="col-12 m-auto ">
        			                <img  src="images/company.png"  width="220px" height="220px" className=" rounded" alt="image_company"/>
        			            </div>
							</div>
							<div className='row'>
								<div className='col-6'>
									<h6 className='font-weight-bold'>Raison social :</h6>
								</div>
        			        	<div className="col-6 ">
									<h6 className="">{com.Raisonsocial}</h6>
								</div>
							</div>
							<div className='row'>
								<div className='col-6'>
									<h6 className='font-weight-bold'>Responsable :</h6>
								</div>
        			        	<div className="col-6 ">
									<h6 className="">{com.Responsable}</h6>
								</div>
							</div>
							<div className='row'>
								<div className='col-6'>
									<h6 className='font-weight-bold'>RTribunal :</h6>
								</div>
        			        	<div className="col-6 ">
									<h6 className="">{com.Tribunal}</h6>
								</div>
							</div>
							<div className='row'>
								<div className='col-6'>
									<h6 className='font-weight-bold'>Origine de fonds :</h6>
								</div>
        			        	<div className="col-6 ">
									<h6 className="">{com.Originedefonds}</h6>
								</div>
							</div>
							<div className='row'>
								<div className='col-6'>
									<h6 className='font-weight-bold'>Telephon :</h6>
								</div>
        			        	<div className="col-6 ">
									<h6 className="">{com.Telephon}</h6>
								</div>
							</div>
						</div>
					</div>
				</div>
			<div className="col-md-7 grid-margin transparent">
              <div className="row">
                <div className="col-md-6 mb-4 stretch-card transparent">
                  <div className="card card-tale">
                    <div className="card-body">
                      <p className=" fs-20 mb-4"> Total TVA </p>
                      <p className="fs-30 mb-2">{com.TVA === undefined || Object.keys(com.TVA).length <= 0 || TVA.length === 0 ? 0 : TVA.TotalResteNew} Dh Dh</p>
                      {/* <p>10.00% (30 days)</p> */}
                    </div>
                  </div>
                </div>
                <div className="col-md-6 mb-4 stretch-card transparent">
                  <div className="card card-dark-blue">
                    <div className="card-body">
                      <p className="fs-20 mb-4">Total Reste TVA</p>
                      <p className="fs-30 mb-2">{com.TVA === undefined || Object.keys(com.TVA).length <= 0 || TVA.length === 0 ? 0 : TVA.ResteNew} Dh</p>
                      {/* <p>22.00% (30 days)</p> */}
                    </div>
                  </div>
                </div>
              </div>
			  <div className="row">
                <div className="col-md-6 mb-4 stretch-card transparent">
                  <div className="card card-tale">
                    <div className="card-body">
                      <p className=" fs-20 mb-4"> Total CNSS</p>
                      <p className="fs-30 mb-2">{(com.CNSS === undefined || Object.keys(com.CNSS).length <= 0 || CNSS.length === 0) ? 0 : CNSS.TotalResteNew}  Dh</p>
                      {/* <p>10.00% (30 days)</p> */}
                    </div>
                  </div>
                </div>
                <div className="col-md-6 mb-4 stretch-card transparent">
                  <div className="card card-dark-blue">
                    <div className="card-body">
                      <p className="fs-20 mb-4">Total Reste CNSS</p>
                      <p className="fs-30 mb-2">{(com.CNSS === undefined || Object.keys(com.CNSS).length <= 0 || CNSS.length === 0) ? 0 : CNSS.ResteNew} Dh</p>
                      {/* <p>22.00% (30 days)</p> */}
                    </div>
                  </div>
                </div>
              </div>
              <div className="row">
                <div className="col-md-6 mb-4 mb-lg-0 stretch-card transparent">
                  <div className="card card-light-blue">
                    <div className="card-body">
                      <p className="fs-20 mb-4">Paye </p>
                      <p className="fs-30 mb-2">{  com.TVA === undefined  || Object.keys(com.TVA).length <= 0 || TVA.length === 0 ? 0 : TVA.Paye} Dh</p>
                      {/* <p>2.00% (30 days)</p> */}
                    </div>
                  </div>
                </div>
                <div className="col-md-6 stretch-card transparent">
                  <div className="card card-light-danger">
                    <div className="card-body">
                      <p className="fs-20 mb-4">Total Reste</p>
                      <p className="fs-30 mb-2">{  ( com.CNSS === undefined || Object.keys(com.CNSS).length <= 0 || CNSS.length === 0 ? 0 : CNSS.ResteNew)+ (com.TVA === undefined || Object.keys(com.TVA).length <= 0 || TVA.length === 0 ? 0 : TVA.ResteNew )} Dh</p>
                      {/* <p>0.22% (30 days)</p> */}
                    </div>
                  </div>
                </div>
              </div>
			  
            </div>
		</div>
		<div className='row'>
		<div className="col-lg-6 grid-margin stretch-card p-0 mr-2">
			<div className="card">
				<div className="card-body">
					<div  className="row">
						<div className='row col-12'>
							<div className='col-6'>  
								<h5><strong>Chiffre Daffaire : </strong>{TVA === undefined ||Object.keys(com.TVA).length === 0 || TVA.length === 0 ? 0 : TVA.ChiffreDaffaire } Dh</h5>
							</div>
							<div className='col-6'>
								<h3 className='float-right'><strong>TVA</strong></h3>
							</div>
						</div>
                	   <div  className="col-12">
                	     <div  className="table-responsive">
                	       <table className="display expandable-table table-striped" style={{width:"100%"}}>
								<thead>
									<tr>
										<th>Le Mois</th>
										<th>Payé</th>
										<th>Deposit</th>
										<th>Modifer</th>
									</tr>
								</thead>
								<tbody>
									{  com.TVA === undefined || Object.keys(com.TVA).length === 0 || TVA.length === 0 ? null : TVA.TVA.filter((com) =>
			        				(com !== undefined
            						&& (Object.keys(com).length > 0)))
									.map((tva, index)=> {
										return <tr key={index + 1}>
												<td>{tva.YearDebitCreation} - {tva.monthDebitCreation} </td>
												<td>{tva.Paid ? "Done": "Not Paid"}</td>
												{/* -----********------ */}
												{
													tva.Deposit === "No Deposit" 
													? <td> <label className="badge badge-danger animation_warnning ">No Deposit</label> </td>
													: null
												}
												{
													tva.Deposit === "En Cours" 
													? <td> <label className="badge badge-warning animation_warnning">En Cours</label> </td>
													: null
												}
												{
													tva.Deposit === "Deposit" 
													? <td> <label className="badge badge-success">Deposit</label> </td>
													: null
												}
												<td>
													<button type="button" className="btn btn-info m-0 p-2" data-toggle="modal" data-target={"#" + tva.id+ "CheckDepositModal" + index}>
														Modifier
														<FontAwesomeIcon icon = {faFilePen} className="ml-1"/>
													</button>
																									
													{/* <!-- Modal --> */}
													<div className="modal fade" id={tva.id + "CheckDepositModal" + index} tabIndex="-1" role="dialog" aria-labelledby="DepositModalLabel" aria-hidden="true">
													  <div className="modal-dialog" role="document">
													    <div className="modal-content">
													      	<div className='modal-header p-3'>
															  <h3 className="modal-title" id={index + "tvaexampleModalLabel"}>Deposit TVA Le Mois : {tva.monthDebitCreation} / {tva.YearDebitCreation} </h3>
														  		<button type="button" className="close" 
																	data-dismiss="modal" 
																	aria-label="Close">
        														  <span aria-hidden="true" style={{fontSize : "30px"}}>&times;</span>
        														</button>
														  	</div>
																	  <h4 className='m-2 '> La situation actuelle :  
																		  {
																			tva.Deposit === "No Deposit" 
																			? <label className="badge badge-danger animation_warnning m-2">No Deposit</label> 
																			: null
																		}
																		{
																			tva.Deposit === "En Cours" 
																			?  <label className="badge badge-warning animation_warnning m-2">En Cours</label> 
																			: null
																		}
																		{
																			tva.Deposit === "Deposit" 
																			?  <label className="badge badge-success m-2">Deposit</label> 
																			: null
																		}
																		   </h4>
													      <div className="row col-12 m-auto">
													        <button type="button" className="btn btn-success m-1 col-sm" 	value="Deposit" onClick={(e)=> checkDepositTva(e.target.value, com, 	index)} data-dismiss="modal">Deposit</button>
													        <button type="button" className="btn btn-warning m-1 col-sm" value="En Cours" onClick={(e)=> checkDepositTva(e.target.value, com, index)} data-dismiss="modal">En Cours</button>
															<button type="button" className="btn btn-danger m-1 col-sm" value="No Deposit" onClick={(e)=> checkDepositTva(e.target.value, com, index)} data-dismiss="modal">No Deposit</button>
													      </div>
														  
													    </div>
													  </div>
													</div>
												</td>
												</tr>
										}) }
								</tbody>
							</table>
						</div>
					   </div>
					</div>
  				</div>
  			</div>		
		   </div>
		<div className="col-lg-5 grid-margin stretch-card p-0 ">
			<div className="card">
				<div className="card-body">
					<div  className="row">
					<div className='row col-12'>
							<div className='col-6'>  
								<h5><strong>Nombre Salaries : </strong>{CNSS === undefined || Object.keys(com.TVA).length === 0 || CNSS.length === 0 ? 0 : CNSS.NombreSalaries }</h5>
							</div>
							<div className='col-6'>
								<h3 className='float-right'><strong>CNSS</strong></h3>
							</div>
						</div>
                	   <div  className="col-12">
                	     <div  className="table-responsive">
                	       <table className="display expandable-table table-striped" style={{width:"100%"}}>
								<thead>
									<tr>
										<th>Le Mois</th>
										<th>Payé</th>
										<th>Deposit</th>
										<th>Modifer</th>
									</tr>
								</thead>
								<tbody>
									
								{ com.CNSS === undefined ||Object.keys(com.CNSS).length === 0 || CNSS.length === 0 ? null : CNSS.CNSS.filter((com) =>
			        				(com !== undefined
            						&& (Object.keys(com).length > 0)))
									.map((cnss, index)=> {
										return <tr key={index + 1}>
												<td>{cnss.YearDebitCreation} - {cnss.monthDebitCreation} </td>
												<td>{cnss.Paid ? "Done": "Not Paid"}</td>
												{/* -----********------ */}
												{
													cnss.Deposit === "No Deposit" 
													? <td> <label className="badge badge-danger animation_warnning ">No Deposit</label> </td>
													: null
												}
												{
													cnss.Deposit === "En Cours" 
													? <td> <label className="badge badge-warning animation_warnning">En Cours</label> </td>
													: null
												}
												{
													cnss.Deposit === "Deposit" 
													? <td> <label className="badge badge-success">Deposit</label> </td>
													: null
												}
												<td>
													<button type="button" className="btn btn-info m-0 p-2" data-toggle="modal" data-target={"#" + cnss.id+ "cnssCheckDepositModal" + index}>
														Modifier
														<FontAwesomeIcon icon = {faFilePen} className="ml-1"/>
													</button>		
													{/* <!-- Modal --> */}
													<div className="modal fade" id={cnss.id + "cnssCheckDepositModal" + index} tabIndex="-1" role="dialog" aria-labelledby="DepositModalLabel" aria-hidden="true">
													  <div className="modal-dialog" role="document">
													    <div className="modal-content">
													      	<div className='modal-header p-3'>
															  <h3 className="modal-title" id={index + "cnssexampleModalLabel"}>Deposit TVA Le Mois : {cnss.monthDebitCreation} / {cnss.YearDebitCreation} </h3>
														  		<button type="button" className="close" 
																	data-dismiss="modal" 
																	aria-label="Close">
        														  <span aria-hidden="true" style={{fontSize : "30px"}}>&times;</span>
        														</button>
														  	</div>
																	  <h4 className='m-2 '> La situation actuelle :  
																		  {
																			cnss.Deposit === "No Deposit" 
																			? <label className="badge badge-danger animation_warnning m-2">No Deposit</label> 
																			: null
																		}
																		{
																			cnss.Deposit === "En Cours" 
																			?  <label className="badge badge-warning animation_warnning m-2">En Cours</label> 
																			: null
																		}
																		{
																			cnss.Deposit === "Deposit" 
																			?  <label className="badge badge-success m-2">Deposit</label> 
																			: null
																		}
																		   </h4>
													      <div className="row col-12 m-auto">
													        <button type="button" className="btn btn-success m-1 col-sm" 	value="Deposit" onClick={(e)=> checkDepositCnss(e.target.value, com, 	index)} data-dismiss="modal">Deposit</button>
													        <button type="button" className="btn btn-warning m-1 col-sm" value="En Cours" onClick={(e)=> checkDepositCnss(e.target.value, com, index)} data-dismiss="modal">En Cours</button>
															<button type="button" className="btn btn-danger m-1 col-sm" value="No Deposit" onClick={(e)=> checkDepositCnss(e.target.value, com, index)} data-dismiss="modal">No Deposit</button>
													      </div>
														  
													    </div>
													  </div>
													</div>
												</td>
												</tr>
										}) }
								</tbody>
							</table>
						</div>
					   </div>
					</div>
  				</div>
  			</div>		
		   </div>
		   </div>
		</div>
  )
}