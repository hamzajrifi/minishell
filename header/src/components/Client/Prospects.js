import React, { useState , useEffect } from 'react';

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {	faFileImport, faFilePen , faTrashCan, faUserPlus
} from "@fortawesome/free-solid-svg-icons";
import  CompanyContext  from '../../context/EntreprisesContext';
import NewClinet from './NewClinet';


const ProspectsList = ({getProspectId, allwedForm, getToClientId}) => {
    const [prospects, setProspects] = useState([]);
    const [datasearch, setsearch] = useState("");
    const [filtersearch, setfiltersearch] = useState("Raisonsocial");
    var retnbr = 0;

  useEffect (() => {
    getProspects();
  }, []);
  const getProspects = async () => {
    const data = await CompanyContext.getAllprospects();
    setProspects(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
  };
  const deleteHandler = async(id) => {
    await CompanyContext.deleteprospect(id);
    getProspects();
  };
  const checkfilter = (e) => {
    if(filtersearch === "Raisonsocial")
      return e.Raisonsocial;
    else if (filtersearch === "Responsable")
      return e.Responsable;
  }
  const checkallwedForm = () => {
    getProspectId("");
    allwedForm();
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
                    Ajouter une nouvelle Prospect
                </button>
                <button type='button'
                    className="btn btn btn-dark btn-rounded btn-icon"
                    onClick={getProspects}
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
                              <th>#</th>
                              <th>Raison social</th>
                              <th>Responsable</th>
                              <th>Date de ngagement</th>
                              <th>Telephon</th>
                              <th></th>
                              <th></th>
                              <th></th>
                            </tr>
                          </thead>
                          <tbody>
                             {retnbr = prospects.filter((com) =>
			                        (checkfilter(com).toLowerCase().includes(datasearch)
			                        || checkfilter(com).toUpperCase().includes(datasearch) 
                              || checkfilter(com).includes(datasearch) 
                                  	)).map( (com , index)=>   {
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
                                  <h6>{com.Datedengagement}</h6>
                                </td>
                                <td>
                                  <h6>{com.Telephon}</h6>
                                </td>
                                <td>
                                  <button 
                                      className="btn btn-warning m-0 p-2"
                                      onClick={(e)=> getProspectId(com.id)}
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
                                          
                                          <div className="modal-body">
                                            are you sure you want to delete this company...
                                          </div>
                                          <div className="modal-footer">
                                            <button type="button" className="btn btn-secondary" data-dismiss="modal">Close</button>
                                            <button 
                                                  className="btn btn-scend m-0 p-3"
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
                                      className="btn btn-primary p-2 m-0 m-2 mr-4"
                                      onClick={(e)=> getToClientId(com.id)}
                                  >
                                      Transfert aux clients
                                      <FontAwesomeIcon icon = {faFileImport} className="ml-1"/>
                                </button>
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
                  <div>

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


function Prospects({datainfoUser}) {
    const [prospectId, setProspectId] = useState("");
    const [showForm, setShowForm] = useState(false);
    const allwedForm = () => setShowForm(true);
    const hidedForm = () => setShowForm(false);
    const [checkdb,setcheckdb] = useState("");

  const getProspectIdHandler = (id) => {
    allwedForm();
    setProspectId(id);
  };
  const getToClientHundler = (id) => {
    setcheckFormToclient(false);
    allwedForm();
    setcheckdb("ToClient");
    setProspectId(id);
  };
  // ediite 
  const [checkFormToClient, setcheckFormToclient] = useState(true);

  return (
    <div>    
      { showForm ? <NewClinet datainfoUser={datainfoUser} id={prospectId} setProspectId={setProspectId} hideForm={hidedForm} checkdb={checkdb} checkFormToClient={checkFormToClient} /> :null}
        
        <ProspectsList getProspectId={getProspectIdHandler} allwedForm={allwedForm} getToClientId={getToClientHundler}/>
    </div>
  )
}

export default  Prospects;
