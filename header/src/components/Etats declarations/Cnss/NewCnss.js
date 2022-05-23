import React, { useEffect, useState } from 'react'
import CompanyContext from "../../../context/EntreprisesContext";
import { Outlet } from 'react-router-dom';


const  NewCNSS = ({ hideForm, companyId, cheackDecCnss}) => {
	
	// declaration
	const [message, setMessage] = useState ({error : false, msg: ""});
	const [companies, setCompanies] = useState([]);
	const [filtersearch, setfiltersearch] = useState("Raisonsocial");
	const [datasearch, setsearch] = useState("");
	const [hidelistsearch, setHidelistsearch] = useState(false);
	const [Datepaiment, setDatepaiment] = useState(new Date().toLocaleString());
	const [NombreSalaries , setNombreSalaries ] = useState(0);
	const [monthDebitCreation, setmonthDebitCreation] = useState(0);
	const [YearDebitCreation, setYearDebitCreation] = useState(0);
	const [PriceMonthHt, setPriceMonthHt] = useState(0);
	const [PriceMonthTtc, setPriceMonthTtc] = useState(0);
	const [AnnuelleHt,   setAnnuelleHt] = useState(0);
	const [AnnuelleTtc,  setAnnuelleTtc] = useState(0);
	const [ResteNew, setResteNew] = useState(0);
	const [TotalResteNew, setTotalResteNew] = useState(0);
	const [ResteMensuelleHt, setResteMensuelleHt] = useState(0);
	const [ResteMensuelleTtc, setResteMensuelleTtc] = useState(0);
	const [ResteAnnuelleHt, setResteAnnuelleHt] = useState(0)
	const [ResteAnnuelleTtc, setResteAnnuelleTtc] = useState(0)
	const [Paye, setPaye] = useState(0);
	const [RemiseMad, setRemiseMad] = useState(0);
	const [RemisePercentage, setRemisePercentage] = useState(0);
	const [isSubDisable ,  setisSubDisable] = useState("");
	const [Id, setId] = useState("");

	////
	var ht = 0;
	var ttc = 0;
	var dmonth = 0;
	var dyear = 0;
	var CNSS = [];
	var allpaiement = [];
	var allDatepaiement = [];
	var allDestinataire = [];
	////

	
	// get date today
	var dt = new Date();
	var month = dt.getMonth();
	var year = dt.getFullYear();
	////e

	// function allow list search
    const inputsearch =(e)=>{
		setHidelistsearch(false);
		setsearch(e);
	};
	////

	  // function get data companies
  	const getCompanies = async () => {
		const data = await CompanyContext.getAllcompanies();
		setCompanies(data.docs.map((doc)=> ({...doc.data(), id: doc.id})))
	};
	////

	// function check NombreSalaries  
	const checkNombreSalaries  =(e)=>{
		const nbr = parseInt(e);
		if (isNaN(e) || e === "") 
		{
			if (e === "") { 
				setNombreSalaries (0); 
				ClearData();
			}
			return;
		}
		setNombreSalaries (nbr);
		if (e <= 5 )
      	{
			  ht = 300;
			  ttc = 360;
	  	}
		else if (e > 5 && e <= 10)
		{
			ht = 500;
			ttc = 600;
		}
		else if (e > 10)
		{
			ht = 700;
			ttc = 840;
		}
		setPriceMonthHt(ht);
		setPriceMonthTtc(ttc);
		setAnnuelleHt((ht * (13 - monthDebitCreation)) - RemiseMad);
		setAnnuelleTtc((ttc * (13 - monthDebitCreation)) - RemiseMad);
		setResteMensuelleHt(ht);
		setResteMensuelleTtc(ttc);
		setResteAnnuelleHt((ht * (13 - monthDebitCreation)) - RemiseMad);
		setResteAnnuelleTtc((ttc * (13 - monthDebitCreation)) - RemiseMad);
		setResteNew(((month + 1) - monthDebitCreation) * ttc);
		setTotalResteNew((((month + 1) - monthDebitCreation) * ttc));
		if (year > YearDebitCreation && YearDebitCreation > 2000)
		{
			dyear = year - YearDebitCreation;
			dmonth = 13 - monthDebitCreation + month + 1;
			setResteNew(ttc * dmonth * dyear);
			setTotalResteNew(ttc * dmonth * dyear);
		}
	}
	////

	// function check month Debit Creation
	const checkmonthDebitCreation =(nbr)=>{
		if (isNaN(nbr) || nbr === "" || nbr > 12) 
		{
			if (nbr === "") { setmonthDebitCreation(""); }
			return;
		}
		var e = parseInt(nbr);
		setmonthDebitCreation(e);
		setAnnuelleHt((PriceMonthHt * (13 - e)));
		setAnnuelleTtc((PriceMonthTtc * (13 - e)));
		setResteAnnuelleHt((PriceMonthHt * (13 - e)) - RemiseMad - Paye);
		setResteAnnuelleTtc((PriceMonthTtc * (13 - e)) - RemiseMad - Paye);
		setResteNew(((month + 1) - e) * PriceMonthTtc);
		setTotalResteNew(((month + 1) - e) * PriceMonthTtc);
		if (year > YearDebitCreation && YearDebitCreation > 2000)
		{
			dyear = year - YearDebitCreation;
			dmonth = 13 - e + month + 1;
			setResteNew(PriceMonthTtc * dmonth * dyear);
			setTotalResteNew(PriceMonthTtc * dmonth * dyear);
		}
	}
	////

	//// function check year Debit creation 
	const checkYearDebitCreation =(e)=> {
		if (isNaN(e) || e === "" || e > year) 
		{
			if (e === "") { setYearDebitCreation(""); }
			return;
		}
		const nbr = parseInt(e);
		setYearDebitCreation(nbr);
		if (nbr < 2000) {return;}
		ht = (year - nbr);
		setAnnuelleHt(PriceMonthHt * (13 - monthDebitCreation) + (ht * 13 * PriceMonthHt));
		setAnnuelleTtc(PriceMonthTtc * (13 - monthDebitCreation) + (ht * 13 * PriceMonthTtc));
		setResteAnnuelleHt((PriceMonthHt * (13 - monthDebitCreation) + (ht * 13 * PriceMonthHt)) - RemiseMad - Paye);
		setResteAnnuelleTtc((PriceMonthTtc * (13 - monthDebitCreation) + (ht * 13 * PriceMonthTtc)) - RemiseMad - Paye);
		setResteNew(((month + 1) - monthDebitCreation) * PriceMonthTtc);
		setTotalResteNew(((month + 1) - monthDebitCreation) * PriceMonthTtc);
		if (year > e && e > 2000)
		{
			dyear = year - e;
			dmonth = 12 - monthDebitCreation + month + 1;
			setTotalResteNew(PriceMonthTtc * dmonth * dyear);
			setResteNew(PriceMonthTtc * dmonth * dyear);
		}
	}
	////

	// function after choise company
		const Choisecompany =(e)=>{

			setId(e.id);
			setMessage({error : false, msg : ""});
			setsearch(e.Raisonsocial);	
			setHidelistsearch(true);
			setisSubDisable("");
			if (e.CNSS !== undefined && Object.keys(e.CNSS).length > 0 )
			{
				setDatepaiment("");
				setisSubDisable("d-none");
				setMessage({error : true, msg : "cette société a déjà déclaré !"});
				return ;
			}
			ClearData();
			setDatepaiment(new Date().toLocaleString());
			setmonthDebitCreation(month);
			setYearDebitCreation(year);
		}
	////

	// function check client Payer
	const checkPayer =(e)=> {
		if (isNaN(e) || e === "") 
		{
			if (e === "") { 
				setPaye("");
				setResteAnnuelleHt(AnnuelleHt - RemiseMad);
				setResteAnnuelleTtc(AnnuelleTtc - RemiseMad);
				setResteMensuelleHt(PriceMonthHt);
				setResteMensuelleTtc(PriceMonthTtc);
				setResteNew(((month + 1) - monthDebitCreation) * PriceMonthTtc);
			}
			return;
		}
		setPaye(e);
		setResteNew(TotalResteNew - e);
		if (TotalResteNew - e <= 0){
			setResteNew(0);
		}
		setResteAnnuelleHt(AnnuelleHt - e - RemiseMad);
		setResteAnnuelleTtc(AnnuelleTtc - e - RemiseMad);
		if (PriceMonthTtc - e <= 0){
			setResteMensuelleHt(0);
			setResteMensuelleTtc(0);
			return ;
		}
		setResteMensuelleHt(PriceMonthHt - e);
		setResteMensuelleTtc(PriceMonthTtc - e);
	}
	////
	
	// check Remise en MAD
	const checkRemiseMad =(e)=> {
		if (isNaN(e) || e === "") 
		{
			if (e === "") { 
				setRemiseMad("");
				setRemisePercentage("");
				setResteAnnuelleHt(AnnuelleHt - Paye);
				setResteAnnuelleTtc(AnnuelleTtc - Paye);
		 	}
			return;
		}
		var nbr = parseInt(e);
		setRemiseMad(nbr);
		setRemisePercentage(parseFloat((nbr / AnnuelleTtc) * 100).toFixed(3));
		setResteAnnuelleHt(AnnuelleHt - nbr - Paye); 
		setResteAnnuelleTtc(AnnuelleTtc - nbr - Paye);
		return;
	}
	////

	// function check Remise on Percentage
	const checkRemisePercentage =(e)=> {
		if (isNaN(e) || e === "") 
		{
			if (e === "") { 
				setRemisePercentage(""); 
				setRemiseMad("");
				setResteAnnuelleHt(AnnuelleHt - Paye);
				setResteAnnuelleTtc(AnnuelleTtc - Paye);
			}
			return;
		}
		var nbr = parseInt(e);
		setRemiseMad((AnnuelleTtc / 100) * nbr);
		setRemisePercentage(nbr);
		setResteAnnuelleHt(AnnuelleHt - RemiseMad - Paye);
		setResteAnnuelleTtc(AnnuelleTtc - RemiseMad - Paye);
		return;
	}
  	////

	// function check filter
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

	//// function clear all inpute and data
	const ClearData =()=>{

		setNombreSalaries (0);
		setmonthDebitCreation(month);
		setPriceMonthHt(0);
		setPriceMonthTtc(0);
		setResteMensuelleHt(0);
		setResteMensuelleTtc(0);
		setResteAnnuelleHt(0);
		setResteAnnuelleTtc(0);
		setRemiseMad(0);
		setRemisePercentage(0);
		setResteNew(0);
		setDatepaiment(new Date().toLocaleString());
		setPaye(0);
	}
	////

	// function submit form
	const handelSubmit = async  (e) => {
		e.preventDefault();
		if (datasearch === "" 
			|| NombreSalaries  === 0 
			|| Id === undefined 
			|| YearDebitCreation === 0 
			|| monthDebitCreation === 0 ){
				setMessage({error : true, msg : "Tous les champs sont obligatoires!"});
				return ;
		}
		allpaiement.push(Paye);
		allDatepaiement.push(Datepaiment);
		var dmonth = monthDebitCreation;
		var dyear = YearDebitCreation; 
		var Paid = false;
		var res = Paye;
		var TmpMonth = month;
		dyear = parseInt(dyear);
		while(year >= dyear)
		{
			if (year !== dyear)
			{
				TmpMonth = 12;
				dmonth = 1;
			}
			else if (year !== YearDebitCreation){
				TmpMonth = month;
				dmonth = 1;
			};
			if (dyear === YearDebitCreation)
			{
				dmonth = monthDebitCreation;
			}
			while(TmpMonth  >= dmonth)
			{
				res = res - PriceMonthTtc;
				if (res >= 0) { Paid = true ;}
				else {Paid = false}
				CNSS.push (
					{
						YearDebitCreation : dyear,
						monthDebitCreation : dmonth,
						Paid ,
						Deposit : "No Deposit",
						historyPaiment : {
							allpaiement,
							allDatepaiement ,
							allDestinataire,
						},
					}
				);
				dmonth++;
			}
			dyear++;
		}
		const NewCnss = {
			CNSS : {
				CNSS,
				month,
				year,
				Paye,
				NombreSalaries ,
				PriceMonthHt,
				PriceMonthTtc,
				AnnuelleHt,
				AnnuelleTtc,
				ResteNew,
				TotalResteNew,
				ResteAnnuelleHt,
				ResteAnnuelleTtc,
				RemiseMad,
				RemisePercentage,
			}
		};
		try {
			if (Id !== undefined && Id !== "")
			{
				await CompanyContext.updatecompany(Id, NewCnss);
      	      	setMessage({error : false, msg : "Nouveau Declaration De CNSS ajouté avec succès!" });
			}
		} catch (err) {
			setMessage({error : true, msg : err.message});
		}
		ClearData();
		setsearch("");
	}
	////

	//// use Effect 
	useEffect (() =>{
		getCompanies();
	},[]);

	////////////////////---------------------------------/////////////////////

  return (
    
	  <div className="card">
	    <div className="card-body pt-0">
	    <h1 className=" text-center" >Decalaration De CNSS</h1>
      	<h2>
      	    {message.msg && 
      	    (<div 
      	      	className={message.error ? "erroremessage" : "successmessage"}
      	        variant = {message.error ? "danger" : "success"}
      	        dismissible = "false"
      	        onClose = {() => setMessage("")}
      	    >{ message.msg}</div>)}
      	</h2> 
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
      <form onSubmit={handelSubmit} className={isSubDisable}>
        <div className='formCristion'>
          <div className='row'>
            <div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Nombre Salaries </label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          placeholder='0 Dh'
						  value={NombreSalaries }
						  onChange = {(e) => checkNombreSalaries (e.target.value)}
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
                          value={Datepaiment}
                          onChange = {(e) => setDatepaiment(e.target.value)}
                          />
                </div>
              </div>
            </div>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Le mois debit creation</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          placeholder='mois'
                          value={monthDebitCreation}
                          onChange = {(e) => checkmonthDebitCreation(e.target.value)}
                          />
                </div>
              </div>
            </div>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Le Annuelle debit creation</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          placeholder='année'
                          value={YearDebitCreation}
                          onChange = {(e) => checkYearDebitCreation(e.target.value)}
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
                          value={PriceMonthHt}
                          readOnly
                          />
                </div>
              </div>
            </div>
            <div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Prix TTC</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          value={PriceMonthTtc}
                          readOnly
                            />
                </div>
              </div>
            </div>
          </div>
          <div className='row'>
            <div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Reste Mensuelle HT</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          value={ResteMensuelleHt}
                          readOnly/>
                </div>
              </div>
            </div>
            <div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Reste Mensuelle TTC</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          value={ResteMensuelleTtc}
                          readOnly
                           />
                </div>
              </div>
            </div>
          </div>
		  <div className='row'>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">le reaste Annuelle HT</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
						  value={ResteAnnuelleHt}
						  readOnly
                          />
                </div>
              </div>
            </div>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">le reaste Annuelle TTC</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
						  value={ResteAnnuelleTtc}
						  readOnly
                          />
                </div>
              </div>
            </div>
          </div>
			<div className='row'>
			  <div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Remise on MAD</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          value={RemiseMad}
                          onChange = {(e) => checkRemiseMad(e.target.value)}
                          />
                </div>
              </div>
            </div>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Remise on Pourcentage %</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          value={RemisePercentage}
                          onChange = {(e) => checkRemisePercentage(e.target.value)}
                          />
                </div>
              </div>
            </div>
          </div>
		  <div className='row'>
            <div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Paye</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          value={Paye}
                          onChange = {(e) => checkPayer(e.target.value)}
                          />
                </div>
              </div>
            </div>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Totale Reste Actualite</label>
                <div className="col-sm-8">
                  <h3> {ResteNew} Dh</h3>
                </div>
              </div>
            </div>
			</div>
			
        </div>
                          
		<button type="submit" className = "btn button-right btn-scend btn-icon-text mr-2" ><i className="ti-file btn-icon-prepend"></i>Submit</button>
      </form>
      <div className="">
		<button className="btn button-right btn-inverse-dark mr-2" onClick={hideForm}>Cancel</button>
      </div>
      <Outlet/>
              </div>
          </div>
  )
}


export default NewCNSS;

