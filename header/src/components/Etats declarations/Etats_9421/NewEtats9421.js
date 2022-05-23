import React, { useEffect, useState } from 'react';
import CompanyContext from "../../../context/EntreprisesContext"
import { Outlet } from 'react-router-dom';

function NewEtats9421({hideForm}) {
    const [message, setMessage] = useState ({error : false, msg: ""});
	const [companies, setCompanies] = useState([]);
	const [datasearch, setsearch] = useState("");
	const [hidelistsearch, setHidelistsearch] = useState(false);
    const [inputDatepaiment, setinputDatepaiment] = useState(new Date().toLocaleString());
    const [ht, setHT] = useState("GRATUITE");
    const [ttc, setTtc] = useState("GRATUITE");
    const [idCompany, setIdCompany] = useState("");
	const typeService = "ETAT 9421 ";
    // const [datePaiment, setDatePaiment] = useState([]);
    // const [destinataire, setDestinataire] = useState ([]);
    const [filtersearch, setfiltersearch] = useState("Raisonsocial");

    var datePaiment = [];
    
    const getCompanies = async () => {
        const data = await CompanyContext.getAllcompanies();
          setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
    };

    const inputsearch =(e)=>{
        setHidelistsearch(false);
        setsearch(e);
    };
      
    const Choisecompany =(e) =>{
        setMessage({error : false, msg : ""});
        setsearch(e.Raisonsocial);
        setIdCompany(e.id);
        setHidelistsearch(true);
    };

    const handelSubmit = async (e) => {
        e.preventDefault();
        if (datasearch === "" || inputDatepaiment === "")
        {
          setMessage({error : true, msg : "Tous les champs sont obligatoires!"});
          return ;
        }
        datePaiment.push(inputDatepaiment);
        const newService  = {
            Etats9421 :{
                typeService,
                ht,
                ttc,
                historyPaiment : {
                datePaiment ,
                // destinataire,
                },
            }
        };
        try {
            if (idCompany !== undefined && idCompany !== "")
            { 
              await CompanyContext.updatecompany(idCompany , newService);
              setMessage({error : false, msg : "Nouveau service ajouté avec succès!" });
            }
            }catch (err)
            {
              setMessage({error : true, msg : err.message});
            }
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
    useEffect (() => {
        getCompanies();
    },[]);

return (
    <div className="col-12 grid-margin">
              <div className="card">
                <div className="card-body">
                <h1 className=" text-center" >Ajouter un Nouveau ETAT 9421 </h1>
        <h1>  
            {message.msg && 
            (<div 
              className={message.error ? "erroremessage" : "successmessage"}
                variant = {message.error ? "danger" : "success"}
                    dismissible = "false"
                    onClose = {() => setMessage("")}
                >{ message.msg}</div>)}
            </h1> 
        <div>
        <div className='pb-4'>
            <div className="input-group mb-0">
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
                <ul className="list-search ">
              
                  {datasearch === "" || hidelistsearch ? null
                  	: companies.filter((com) =>
			        (checkfilter(com).toLowerCase().includes(datasearch)
			        || checkfilter(com).toUpperCase().includes(datasearch) 
              || checkfilter(com).includes(datasearch) 
                  	)).map( (com , index)=>  {
                  return (
                    <li  className='list-group-item' key={index + 1}
                      onClick={ () => Choisecompany(com)}>
                        {checkfilter(com)}
                    </li>
              );
              })}
            </ul>
        </div>
      </div>
        <form onSubmit={handelSubmit}>
          <div className='formCristion'>
            <div className='row'>
              <div className="col-md-6">
                <div className="form-group row">
                  <label className="col-sm-4 col-form-label">Service</label>
                  <div className="col-sm-8">
                  <input  type="text" 
                            className="form-control"
                            value={typeService}
                            readOnly
                            />
                  </div>
                </div>
              </div>
              <div className="col-md-6">
                <div className="form-group row">
                  <label className="col-sm-4 col-form-label">Date de Creation</label>
                  <div className="col-sm-8">
                    <input  type="text" 
                            className="form-control"
                            placeholder='dd-mm-yy'
                            value={inputDatepaiment}
                            onChange = {(e) => setinputDatepaiment(e.target.value)}
                            />
                  </div>
                </div>
              </div>
            </div>
            <div className='row'>
              <div className="col-md-6">
                <div className="form-group row">
                  <label className="col-sm-4 col-form-label">Prix HT</label>
                  <div className="col-sm-8">
                    <input  type="text" 
                            className="form-control"
                            value={ht}
                            onChange = {(e) => setHT(e.target.value)}
                            readOnly
                            />
                  </div>
                </div>
              </div>
              <div className="col-md-6">
                <div className="form-group row">
                  <label className="col-sm-4 col-form-label">Prix HT</label>
                  <div className="col-sm-8">
                    <input  type="text" 
                            className="form-control"
                            value={ttc}
                            onChange = {(e) => setTtc(e.target.value)}
                            readOnly
                            />
                  </div>
                </div>
              </div>
            </div>
          </div>
                <button type="submit" className = "btn button-right btn-scend btn-icon-text mr-2"><i className="ti-file btn-icon-prepend"></i>Submit</button>
        </form>
        <div className="">
		        <button className="btn button-right btn-inverse-dark mr-2" onClick={hideForm}>Cancel</button>

        </div>
        <Outlet/>
                </div>
            </div>
          </div>
)
}
export default NewEtats9421; 