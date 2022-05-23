import React , { useState, useEffect } from "react";
import CompanyContext from "../../context/EntreprisesContext";

const FormClinet = ({id, setCompanyId, hideForm, checkdb, datainfoUser})=> {

  const [Raisonsocial, setNewRaisonsocial] = useState("");
  const [Responsable, setNewResponsable] = useState("");
  const [Datedengagement, setNewDatedengagement] = useState(new Date().toLocaleString());
  const [Telephon, setNewTelephon] = useState("");
  const [Address, setNewAddress] = useState("");
  const [Datedecreation, setNewDatedecreation] = useState(new Date().toLocaleString());
  const [Originedefonds, setNewOriginedefonds] = useState("");
  const [Tribunal, setNewTribunal] = useState("");
  const [Typecompany, setNewTypecompany] = useState("Normale");
  const [codeacces, setNewcodeacces] = useState("");
  const [MotsDepasseAdhesion, setNewMotsDepasseAdhesion] = useState("");
  const [LoginDgi, setNewLoginDgi] = useState("");
  const [MotDePasseDGI, setNewMotDePasseDGI] = useState("");
  const [LoginDamancom, setNewLoginDamancom] = useState("");
  const [MotDePasseDamancom, setNewMotDePasseDamancom] = useState("");
  const [ice, setNewIce] = useState("");
  const [newif, setNewIf] = useState("");
  const [rc, setNewRc] = useState("");
  const [cnss, setNewCnss] = useState("");
  
  const [message, setMessage] = useState ({error : false, msg: ""});
  
  const handelSubmit = async (e) => {
    e.preventDefault();
      if (Raisonsocial === "" || Responsable === "" || Datedengagement === "" || Telephon === ""
          || Address === "" || Datedecreation === "" || Originedefonds === "" 
          || Tribunal === "" || Typecompany === "" )
        {
          setMessage({error : true, msg : "Tous les champs sont obligatoires!"});
          return ;
        }
      const newCompany = {
        Raisonsocial,
        Responsable,
        Datedengagement,
        Telephon,
        Address,
        Datedecreation,
        Originedefonds,
        Tribunal,
        Typecompany,
        acces :{
          codeacces,
          MotsDepasseAdhesion,
          LoginDgi,
          MotDePasseDGI,
          LoginDamancom,
          MotDePasseDamancom
        },
        matricule :{
          ice,
          newif,
          rc,
          cnss
        }
        
      };
      try {
        if (checkdb === "ToClient")
        {
         	await CompanyContext.addCompaniens(newCompany);
         	setMessage({error : false, msg : "New Prospect added successfully!" });
         	await CompanyContext.deleteprospect(id);
        }
        else {
          if (id !== undefined && id !== "")
          {
            await CompanyContext.updatecompany(id, newCompany);
            setCompanyId("");
            setMessage({error : false, msg : "Mise à jour réussie!" });
          }else
          {
            await CompanyContext.addCompaniens(newCompany);
            setMessage({error : false, msg : "New Clinet added successfully!" });
          }
        }
        
      } catch (err)
      {
        setMessage({error : true, msg : err.message});
      }
      setNewRaisonsocial("");
      setNewResponsable("");
      setNewDatedengagement("");
      setNewTelephon("");
      setNewAddress("");
      setNewDatedecreation("");
      setNewOriginedefonds("");
      setNewTribunal("");
      setNewTypecompany("Normale");
      setNewcodeacces("");
      setNewMotsDepasseAdhesion("");
      setNewLoginDgi("");
      setNewMotDePasseDGI("");
      setNewLoginDamancom("");
      setNewMotDePasseDamancom("");
      setNewIce("");
      setNewIf("");
      setNewRc("");
      setNewCnss("");
    };
    const editHandler = async () => {
      setMessage("");
      try {
        if (checkdb === "ToClient")
        {
          const docSnap = await CompanyContext.getProspect(id);
          setNewRaisonsocial(docSnap.data().Raisonsocial);
          setNewResponsable(docSnap.data().Responsable);
          setNewDatedengagement(docSnap.data().Datedengagement);
          setNewTelephon(docSnap.data().Telephon);
        }
        else {
          const docSnap = await CompanyContext.getcompany(id);
          setNewRaisonsocial(docSnap.data().Raisonsocial);
          setNewResponsable(docSnap.data().Responsable);
          setNewDatedengagement(docSnap.data().Datedengagement);
          setNewTelephon(docSnap.data().Telephon);
          setNewAddress(docSnap.data().Address);
          setNewDatedecreation(docSnap.data().Datedecreation);
          setNewOriginedefonds(docSnap.data().Originedefonds);
          setNewTribunal(docSnap.data().Tribunal);
          setNewTypecompany(docSnap.data().Typecompany);
          setNewcodeacces(docSnap.data().acces.codeacces);
          setNewMotsDepasseAdhesion(docSnap.data().acces.MotsDepasseAdhesion);
          setNewLoginDgi(docSnap.data().acces.LoginDgi);
          setNewMotDePasseDGI(docSnap.data().acces.MotDePasseDGI);
          setNewLoginDamancom(docSnap.data().acces.LoginDamancom);
          setNewMotDePasseDamancom(docSnap.data().acces.MotDePasseDamancom);
          setNewIce(docSnap.data().matricule.ice);
          setNewIf(docSnap.data().matricule.newif);
          setNewRc(docSnap.data().matricule.rc);
          setNewCnss(docSnap.data().matricule.cnss);
        }
      }catch (err) {
        setMessage ({error : true, msg : err.message});
      }
    };
    
    useEffect (()=> {
      if(id !== undefined && id !== "")
        {
          editHandler();
        }
    }, [id]);
return (
          <>
                <h1>
                  {message.msg && 
                  (<div 
                      className={message.error ? "erroremessage" : "successmessage"}
                      variant = {message.error ? "danger" : "success"}
                          dismissible = "false"
                          onClose = {() => setMessage("")}
                      >{ message.msg}</div>)}
                  </h1> 
                <form className="form-sample" onSubmit={handelSubmit}>
                  <p className="card-description">
                    Personal info 
                  </p>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Raison social</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control"
                          value={Raisonsocial}
                            onChange={(event) => {
                              setNewRaisonsocial(event.target.value);
                            }}
                            />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Responsable</label>
                        <div className="col-sm-8">
                            <input type="text" className="form-control"
                                value={Responsable}
                                onChange={(event) => {
                                  setNewResponsable(event.target.value);
                              }}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Téléphon</label>
                        <div className="col-sm-8">
                          <input type="numbre" className="form-control" 
                              value={Telephon}
                              onChange={(event) => {
                                setNewTelephon(event.target.value);
                              }}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Date d’engagement</label>
                        <div className="col-sm-8">
                          <input className="form-control" placeholder="dd/mm/yyyy"
                              value={Datedengagement}
                              onChange={(event) => {
                                setNewDatedengagement(event.target.value);
                              }}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Address</label>
                        <div className="col-sm-8">
                          <input className="form-control" placeholder="Address....."
                              value={Address}
                              onChange={(event) => {
                                setNewAddress(event.target.value);
                              }}
                          />
                        </div>
                      </div>
                    </div>
					<div className="col-md-6">
                        <div className="form-group row">
                          <label className="col-sm-4 col-form-label">Origine de fonds</label>
                          <div className="col-sm-8">
                            <select className="form-control"
                              value={Originedefonds}
                              onChange={(event) => {
                                setNewOriginedefonds(event.target.value);
                              }}>
                            <option>------------</option>
                            <option>Contrat bail</option>
                            <option>Domiciliation</option>
                          </select>
                        </div>
                      </div>
                    </div>
                  </div>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Date de création</label>
                        <div className="col-sm-8">
                          <input className="form-control" placeholder="dd/mm/yyyy"
                              value={Datedecreation}
                              onChange={(event) => {
                                setNewDatedecreation(event.target.value);
                              }} />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                        <div className="form-group row">
                          <label className="col-sm-4 col-form-label">Origine de fonds</label>
                        <div className="col-sm-8">
                            <select className="form-control"
                              value={Tribunal}
                              onChange={(event) => {
                                setNewTribunal(event.target.value);
                              }}>
                              <option>------------</option>
                              <option>rabat</option>
                              <option>temara</option>
                              <option>casa blanca</option>
                              <option>tange</option>
                          </select>
                        </div>
                      </div>
                    </div>
                  
					{
					 datainfoUser === undefined || !datainfoUser[0] || (datainfoUser[1] !== datainfoUser[2]) 
					 ? null
					 : <div className="col-md-8 mb-4">
					 <div className="form-group row">
					   <label className="col-sm-4 col-form-label">Type Company</label>
					   <div className="col-sm-4">
						   <div className="form-check">
							   <label className="form-check-label">
								 <input type="radio" className="form-check-input" name="optionsRadios" id="optionsRadios2"
											 value="Normale" 
											 onChange={(event) => {
											   setNewTypecompany(event.target.value);
											 }} 
										 />
								 Normale
						   <i className="input-helper"></i></label>
						 </div>
					   </div>
					   <div className="col-sm-4">
						   <div className="form-check">
								  <label className="form-check-label">
									<input type="radio" className="form-check-input" name="optionsRadios" id="optionsRadios1" 
										value="Vip"
										onChange={(event) => {
									   setNewTypecompany(event.target.value);}
									 }/>
									Vip
								  <i className="input-helper"></i></label>
						 </div>
					   </div>
					 </div>
				   	</div>
					}
                  </div>
                  <div className="row">
                  </div>
                  <h5 className="card-description">
                    Accès Company
                  </h5>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Code accès</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control"
                              value={codeacces} 
                              onChange={(event) => {
                                setNewcodeacces(event.target.value);
                              }}/>
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Mots de passe adhésion </label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                            value={MotsDepasseAdhesion} 
                            onChange={(event) => {
                              setNewMotsDepasseAdhesion(event.target.value);
                            }}
                           />
                        </div>
                      </div>
                    </div>
                  </div>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Login DGI</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                              value={LoginDgi}
                              onChange={(event) => {
                                setNewLoginDgi(event.target.value);
                              }}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Mot de passe DGI </label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control"
                                  value={MotDePasseDGI}
                                  onChange={(event) => {
                                    setNewMotDePasseDGI(event.target.value);
                                  }}
                                  />
                        </div>
                      </div>
                    </div>
                  </div>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Login DAMANCOM </label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                                  value={LoginDamancom}
                                  onChange={(event) => {
                                    setNewLoginDamancom(event.target.value);
                                  }}
                                  />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Mot de passe DAMANCOM </label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                                  value={MotDePasseDamancom}
                                  onChange={(event) => {
                                    setNewMotDePasseDamancom(event.target.value);
                                  }}
                          />
                        </div>
                      </div>
                    </div>
                  </div>
                  <h5> Matricule company</h5>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">ICE</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                              value={ice}
                              onChange={(event) => {
                                setNewIce(event.target.value);
                              }}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">IF </label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control"
                                  value={newif}
                                  onChange={(event) => {
                                    setNewIf(event.target.value);
                                  }}
                                  />
                        </div>
                      </div>
                    </div>
                  </div>
                  <div className="row">
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">RC </label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                                  value={rc}
                                  onChange={(event) => {
                                    setNewRc(event.target.value);
                                  }}
                                  />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">CNSS</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                                  value={cnss}
                                  onChange={(event) => {
                                    setNewCnss(event.target.value);
                                  }}
                          />
                        </div>
                      </div>
                    </div>
                  </div>
                  <button type="submit" className = "btn button-right btn-scend btn-icon-text mr-2"><i className="ti-file btn-icon-prepend"></i>Submit</button>
                </form>
                  <button className="btn button-right btn-inverse-dark mr-2" onClick={hideForm}>Cancel</button>
    
		      </>
    )
}


// form prospect

const  FormProsprect =({ id, setProspectId, hideForm}) =>{

    const [Raisonsocial, setNewRaisonsocial] = useState("");
    const [Responsable, setNewResponsable] = useState("");
    const [Datedengagement, setNewDatedengagement] = useState(new Date().toLocaleString());
    const [Telephon, setNewTelephon] = useState(0);
    const [message, setMessage] = useState ({error : false, msg: ""});


    const handelSubmit = async (e) => {
      e.preventDefault();
        if (Raisonsocial === "" || Responsable === "" 
            || Datedengagement === "" || Telephon === "")
          {
            setMessage({error : true, msg : "Tous les champs sont obligatoires!"});
            return ;
          }
        const newProspect = {
          Raisonsocial,
          Responsable,
          Datedengagement,
          Telephon
          
        };
        try {
          if (id !== undefined && id !== "")
          {
            await CompanyContext.updateProspect(id, newProspect);
            setProspectId("");
            setMessage({error : false, msg : "Update successfully!" });
          }else
          {
            await CompanyContext.addPrpspects(newProspect);
            setMessage({error : false, msg : "New Prospect added successfully!" });
          }
        } catch (err)
        {
          setMessage({error : true, msg : err.message});
        }
        setNewRaisonsocial("");
        setNewResponsable("");
        setNewDatedengagement(new Date().toLocaleString());
        setNewTelephon("");
        //hidedForm();
    };
    const editHandler = async () => {
      setMessage("");
      try {
        const docSnap = await CompanyContext.getProspect(id);
        setNewRaisonsocial(docSnap.data().Raisonsocial);
        setNewResponsable(docSnap.data().Responsable);
        setNewDatedengagement(docSnap.data().Datedengagement);
        setNewTelephon(docSnap.data().Telephon);
      }catch (err) {
        setMessage ({error : true, msg : err.message});
      }
    };
    useEffect (()=> {
      if(id !== undefined && id !== "")
        {
          editHandler();
        }
    }, [id]);

    return (
      <>
          
                <h1>
                    {message.msg && 
                    (<div 
                      className={message.error ? "erroremessage" : "successmessage"}
                        variant = {message.error ? "danger" : "success"}
                            dismissible = "false"
                            onClose = {() => setMessage("")}
                        >{ message.msg}</div>)}
                    </h1> 
                <form className={document.location.pathname === "/Addprospect" ?  "form-sample" : "form-sample inlineform" } onSubmit={handelSubmit}>
                  <p className="card-description">
                    Personal info
                  </p>
                  <div className="row">
                    <div className="col-md-6 mb-2">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Raisonsocial</label>
                        <div className="col-sm-8">
                          <input 
                              type="text" 
                              className="form-control" 
                              placeholder="Raisonsocial..."
                              value={Raisonsocial}
                              onChange = {(e) => setNewRaisonsocial(e.target.value)}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6 mb-2">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Responsable</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                              placeholder="Responsable..."
                              value={Responsable}
                              onChange = {(e) => setNewResponsable(e.target.value)}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6 mb-2">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Telephon</label>
                        <div className="col-sm-8">
                          <input type="text" className="form-control" 
                              placeholder="Telephon..."
                              value={Telephon}
                              onChange = {(e) => setNewTelephon(e.target.value)}
                          />
                        </div>
                      </div>
                    </div>
                    <div className="col-md-6 mb-2">
                      <div className="form-group row">
                        <label className="col-sm-4 col-form-label">Datedengagement</label>
                        <div className="col-sm-8">
                          <input className="form-control"
                              placeholder="dd-mm-yyyy"
                              value={Datedengagement}
                              onChange = {(e) => setNewDatedengagement(e.target.value)}
                          />
                        </div>
                      </div>
                    </div>
                    
                  </div>
				  	<button type="submit" className="btn button-right btn-scend btn-icon-text mr-2"><i className="ti-file btn-icon-prepend"></i>Submit</button>
                </form>
                    <button className="btn button-right btn-inverse-dark mr-2" onClick={hideForm}>Cancel</button>
      </>
  );
}

// Nex Cilent
function NewClinet({id, setCompanyId, hideForm, setProspectId, checkdb, datainfoUser, checkFormToClient}) {
  	const [checkFrom, setcheckFrom] = useState(true);
	const hideclientForm = () => setcheckFrom(false);
	const allowcheckForm = () => setcheckFrom(true);
  return (
    <div className="col-12 grid-margin">
    	<div className="card">
    		<div className="card-body">
				
    			{ checkFrom && !checkFormToClient ? <>
						<button className="btn button-right btn-inverse-dark mr-2"
						 onClick={hideclientForm}
						 >Prospect</button>
    				<h4 className="card-title mb-4">Ajouter une nouvelle Client</h4>
    					<FormClinet id={id} setCompanyId={setCompanyId} hideForm={hideForm} datainfoUser={datainfoUser} checkdb={checkdb} />
						</>
    			  :
				  <>
				 	<button className="btn button-right btn-inverse-dark mr-2"
						onClick={allowcheckForm}
					>Client</button>
    				<h4 className="card-title mb-4">Ajouter une nouvelle Prospect</h4>
    			  <FormProsprect hideForm={hideForm} id={id} setProspectId={setProspectId} />
				  </>
    			}
    		</div>
    	</div>
    </div>
  )
}
export default NewClinet;