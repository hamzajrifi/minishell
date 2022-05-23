import React, { useEffect, useState } from 'react'
import { Link } from 'react-router-dom';
import  CompanyContext  from '../context/EntreprisesContext';

export default function TableauDeBord() {
	const [companies, setCompanies] = useState([]);
	var retnbr = 0;

	const getCompanies = async () => {
		const data = await CompanyContext.getAllcompanies();
		  setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
	};
	// function check Deposit
	const checkDeposit = (e, type) => {
		//console.log(e, "/", type);
		console.log()
		if (type === "TVA")
		{
			if (e.TVA.filter((com) => com.Paid === false).length === 0) 
			{ return false; } 
			else {return true};
		}
	}
	/////
	useEffect(() => {
		getCompanies();
	}, []);
  return (
	  <>
    <div  className="row">
    <div  className="col-md-5 grid-margin stretch-card">
      <div  className="card">
        <div  className="card-body">
          <p  className="card-title mb-2">Entrepris No effectue</p>
          <div  className="row">
            <div  className="col-12">
                <div  className="table-responsive">
                    <table className="display expandable-table table-striped" style={{width:"100%"}}>
                        <thead>
				            <tr>
								<th>#</th>
            	            	<th>Raisonsocial</th>
            	            	<th>Responsable</th>
            	            	<th>Effectue</th>
            	            </tr>
                    			</thead>
                    			<tbody>
								{ retnbr =   companies.filter((com) =>
            						com.TVA !== undefined 
            						&& (Object.keys(com.TVA).length > 0)
									&& checkDeposit(com.TVA, "TVA")
									)
            					.map( (com , index)=> {
									return (
										<tr key={com.id}>
												<td>{index + 1}</td>
												<td className="font-weight-bold">{com.Raisonsocial}</td>
                			  					<td  >{com.Responsable}</td>
                			  					<td className="font-weight-medium" ><div  className="badge btn-scend p-2">TVA No effectue</div></td>
                							</tr>
            							);
									})}
              			</tbody>
    		    	</table>
					{!(Array.isArray(retnbr) && retnbr.length) ? 
							<div className="text-center mt-2">aucune Declaration disponible</div>
						: null}
    		      </div>
    		    </div>
    		  </div>
    		</div>
      	</div>
    </div>
    <div  className="col-md-4 stretch-card grid-margin" >
        <div  className="card">
          <div  className="card-body" >
            <p  className="card-title">Les Entrepris</p>
            <ul  className="icon-data-list" style={{ width: "100%", overflow: "auto", height: "375px"}}>
			{ companies.map( (com , index)=> {
            		return (
						<Link 	
									to="/CheckDeposit" 
                            	state={{com: com}}
                            >
							<li key={com.id}>
								<div  className="d-flex">
    							  <img src="images/user-image.png" alt="user"/>
    								<div>
    									<p  className="text-info mb-1">{com.Raisonsocial}</p>
    									<p  className="mb-0">{com.Responsable}</p>
    								</div>
            	   				</div>
            				</li>
						</Link>
            			);
					})}
            </ul>
          </div>
        </div>
      </div>
	  </div>
	  {/*  */}
  {/* 
	  <div  className="row">
            <div  className="col-md-12 grid-margin stretch-card">
              <div  className="card">
                <div  className="card-body">
                  <p  className="card-title">Advanced Table</p>
                  <div  className="row">
                    <div  className="col-12">
                      <div  className="table-responsive">
                        <table id="example"  className="display expandable-table" style={{width:"100%"}}>
                          <thead>
                            <tr>
                              <th>Quote#</th>
                              <th>Product</th>
                              <th>Business type</th>
                              <th>Policy holder</th>
                              <th>Premium</th>
                              <th>Status</th>
                              <th>Updated at</th>
                              <th></th>
                            </tr>
                          </thead>
						  <tbody>
                              	<tr  className="odd">
                              	  	<td  className=" select-checkbox ">Incs234</td>
                              	  	<td  className="sorting_1">Car insurance</td>
                              	  	<td>Business type 1</td>
                              	  	<td>Jesse Thomas</td>
                              	  	<td>$1200</td>
                              	  	<td>In progress</td>
                              	  	<td>25/04/2020</td>
									<td className="nav-item ">
										<a className="nav-link details-control" data-toggle="collapse" href="#ui-basic0" aria-expanded="false" aria-controls="ui-basic0">
											<td className="details-control"></td>
												<span className=" menu-title"></span>
											<i className="menu-arrow"></i>
										</a>
									</td>
                              	</tr>
								<tr className="collapse" id="ui-basic0">
									<ul className="nav flex-column sub-menu">
										<li className="nav-item"> <a className="nav-link" href="/Company">Company</a></li>
										<li className="nav-item"> <a className="nav-link" href="/Prospect">Prospects</a></li>
									</ul>
								</tr>
								<tr  className="odd">
                              	  	<td  className=" select-checkbox">Incs234</td>
                              	  	<td  className="sorting_1">Car insurance</td>
                              	  	<td>Business type 1</td>
                              	  	<td>Jesse Thomas</td>
                              	  	<td>$1200</td>
                              	  	<td>In progress</td>
                              	  	<td>25/04/2020</td>
									<td className="nav-item ">
										<a className="nav-link details-control" data-toggle="collapse" href="#ui-basic1" aria-expanded="false" aria-controls="ui-basic1">
											<td className="details-control"></td>
												<span className=" menu-title"></span>
											<i className="menu-arrow"></i>
										</a>
									</td>
                              	</tr>
								<tr className="collapse" id="ui-basic1">
									<ul className="nav flex-column sub-menu">
										<li className="nav-item"> <a className="nav-link" href="/Company">Company</a></li>
										<li className="nav-item"> <a className="nav-link" href="/Prospect">Prospects</a></li>
									</ul>
								</tr>
								<tr  className="odd">
                              	  	<td  className=" select-checkbox">Incs234</td>
                              	  	<td  className="sorting_1">Car insurance</td>
                              	  	<td>Business type 1</td>
                              	  	<td>Jesse Thomas</td>
                              	  	<td>$1200</td>
                              	  	<td>In progress</td>
                              	  	<td>25/04/2020</td>
									<td className="nav-item ">
										<a className="nav-link details-control" data-toggle="collapse" href="#ui-basic" aria-expanded="false" aria-controls="ui-basic">
											<td className="details-control"></td>
												<span className=" menu-title"></span>
											<i className="menu-arrow"></i>
										</a>
									</td>
                              	</tr>
								<tr className="collapse" id="ui-basic">
									<ul className="nav flex-column sub-menu">
										<li className="nav-item"> <a className="nav-link" href="/Company">Company</a></li>
										<li className="nav-item"> <a className="nav-link" href="/Prospect">Prospects</a></li>
									</ul>
								</tr>
								<tr  className="odd">
                              	  	<td  className=" select-checkbox">Incs234</td>
                              	  	<td  className="sorting_1">Car insurance</td>
                              	  	<td>Business type 1</td>
                              	  	<td>Jesse Thomas</td>
                              	  	<td>$1200</td>
                              	  	<td>In progress</td>
                              	  	<td>25/04/2020</td>
									<td className="nav-item ">
										<a className="nav-link details-control" data-toggle="collapse" href="#ui-basic2" aria-expanded="false" aria-controls="ui-basic2">
											<td className="details-control"></td>
												<span className=" menu-title"></span>
											<i className="menu-arrow"></i>
										</a>
									</td>
                              	</tr>
								<tr className="collapse" id="ui-basic2">
									<ul className="nav flex-column sub-menu">
										<li className="nav-item"> <a className="nav-link" href="/Company">Company</a></li>
										<li className="nav-item"> <a className="nav-link" href="/Prospect">Prospects</a></li>
									</ul>
								</tr>
                          </tbody>
                      </table>
                      </div>
                    </div>
                  </div>
                  </div>
                </div>
              </div>
            </div> */}
			</>
  )
}