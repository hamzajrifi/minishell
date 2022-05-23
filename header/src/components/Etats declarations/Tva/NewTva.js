import React, { useEffect, useState } from 'react'
import CompanyContext from "../../../context/EntreprisesContext";
import { Outlet } from 'react-router-dom';


const  NewTva = ({ hideTva, companyId, cheackDecTva}) => {
	
	// declaration
	const [message, setMessage] = useState ({error : false, msg: ""});
	const [companies, setCompanies] = useState([]);
	const [filtersearch, setfiltersearch] = useState("Raisonsocial");
	const [datasearch, setsearch] = useState("");
	const [hidelistsearch, setHidelistsearch] = useState(false);
	const [Datepaiment, setDatepaiment] = useState(new Date().toLocaleString());
	const [ChiffreDaffaire, setChiffreDaffaire] = useState(0);
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
	var TVA = [];
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

	// function check ChiffreDaffaire 
	const checkChiffreDaffaire =(e)=>{
		const nbr = parseFloat(e);
		
		if (isNaN(nbr)  || /^\s*$/.test(e)) 
		{
			if (e === "") { 
				setChiffreDaffaire(0); 
				ClearData();
			}
			return;
		}
		setChiffreDaffaire(nbr);
		if (e <= 1000000 )
      	{
			  ht = 900;
			  ttc = 1080;
	  	}
		else if (e > 1000000 && e <= 3000000)
		{
			ht = 700;
			ttc = 840;
		}
		else if (e > 3000000 && e <= 5000000)
		{
			ht = 1000;
			ttc = 1200;
		}
		else if (e > 5000000 && e <= 8000000)
      	{
			ht = 1300;
			ttc = 1560;
		}
		else if (e > 8000000)
		{
			ht = 1500;
			ttc = 1800;
		}
		setPriceMonthHt(ht);
		setPriceMonthTtc(ttc);
		if (year > YearDebitCreation && YearDebitCreation > 2000)
		{
			dyear = year - YearDebitCreation - 1;
			dmonth = 13 - monthDebitCreation + month + 1;
			setResteNew(((ttc - RemiseMad) * (dmonth + (dyear * 12))) - Paye);
			setTotalResteNew((ttc - RemiseMad) * dmonth * dyear);

			setAnnuelleTtc(((ttc - RemiseMad) * ((13 - monthDebitCreation) + ((dyear + 1) * 12))));
			setResteAnnuelleTtc(((ttc - RemiseMad) * ((13 - monthDebitCreation) + ((dyear + 1) * 12))) - Paye);

			setAnnuelleHt(((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation + ((dyear + 1)* 12))));
			setResteAnnuelleHt(((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation + ((dyear + 1) * 12))) - ((Paye/ ((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation + (dyear * 12))) * 100) *  (((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation + (dyear * 12))) / 100)));
			return ;
		}
		setAnnuelleHt(((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation)));
		setAnnuelleTtc(((ttc - RemiseMad) * (13 - monthDebitCreation)));
		setTotalResteNew((((month + 1) - monthDebitCreation) * (ttc - RemiseMad)));
		if (ttc - RemiseMad - Paye <= 0)
		{
			setResteMensuelleHt(0);
			setResteMensuelleTtc(0);
		}
		else {
			setResteMensuelleHt(ht - (RemisePercentage * ht/100) - ((Paye / (ttc - RemiseMad)) * 100) * (ht - (RemisePercentage * ht/100) / 100));
			setResteMensuelleTtc(ttc - RemiseMad - Paye);
		}
		if (((ttc - RemiseMad) * (13 - monthDebitCreation) - Paye) <= 0)
		{
			setResteAnnuelleHt(0);
			setResteAnnuelleTtc(0);
		}
		else {
			setResteAnnuelleHt(((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation)) - (Paye / ((ttc - RemiseMad)* (13 - monthDebitCreation)) * ((ht - (RemisePercentage * ht/100)) * (13 - monthDebitCreation))  / 100 ));
			setResteAnnuelleTtc(((ttc - RemiseMad)* (13 - monthDebitCreation) - Paye));
		}
		setResteNew(((month + 1) - monthDebitCreation) * (ttc - (RemisePercentage * ttc/100)) - Paye);
		
	}
	////

	// function check month Debit Creation
	const checkmonthDebitCreation =(nbr)=>{
		if (isNaN(nbr) || nbr === "" || nbr > 12 || /^\s*$/.test(nbr)) 
		{
			if (nbr === "") { setmonthDebitCreation(0);}
			return;
		}
		var e = parseInt(nbr);
		setmonthDebitCreation(e);
		if (year > YearDebitCreation && YearDebitCreation > 2000)
		{
			dyear = year - YearDebitCreation - 1;
			dmonth = 13 - e + month + 1;
			setResteNew(((PriceMonthTtc - RemiseMad) * (dmonth + (dyear * 12))) - Paye);
			setTotalResteNew((PriceMonthTtc - RemiseMad) * dmonth * dyear);

			setAnnuelleTtc(((PriceMonthTtc - RemiseMad) * ((13 - e) + ((dyear + 1) * 12))));
			setResteAnnuelleTtc(((PriceMonthTtc - RemiseMad) * ((13 - e) + ((dyear + 1) * 12))) - Paye);

			setAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - e + ((dyear + 1)* 12))));
			setResteAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - e + ((dyear + 1) * 12))) - ((Paye/ ((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - e + (dyear * 12))) * 100) *  (((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - e + (dyear * 12))) / 100)));
			return ;
		}
		setAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100))  * (13 - e)));
		setAnnuelleTtc(((PriceMonthTtc - RemiseMad) * (13 - e)));
		setResteAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - e)) - (Paye / ((PriceMonthTtc - RemiseMad)* (13 - e)) * ((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - e))  / 100 ));
		setResteAnnuelleTtc(((PriceMonthTtc - RemiseMad) * (13 - e)) - Paye);
		setResteNew((((month + 1) - e) * (PriceMonthTtc - RemiseMad)) - Paye);
		setTotalResteNew(((month + 1) - e) * (PriceMonthTtc - RemiseMad));
		
	}
	////

	//// function check year Debit creation 
	const checkYearDebitCreation =(e)=> {
		if (isNaN(e) || e === "" || e > year || /^\s*$/.test(e)) 
		{
			if (e === "") { setYearDebitCreation(""); }
			return;
		}
		const nbr = parseInt(e);
		setYearDebitCreation(nbr);
		if (nbr < 2000) {return;}
		if (year > e && e > 2000)
		{
			dyear = year - e - 1;
			dmonth = 13 - monthDebitCreation + month + 1;
			setResteNew(((PriceMonthTtc - RemiseMad) * (dmonth + (dyear * 12))) - Paye);
			setTotalResteNew((PriceMonthTtc - RemiseMad) * dmonth * dyear);

			setAnnuelleTtc(((PriceMonthTtc - RemiseMad) * ((13 - monthDebitCreation) + ((dyear + 1) * 12))));
			setResteAnnuelleTtc(((PriceMonthTtc - RemiseMad) * ((13 - monthDebitCreation) + ((dyear + 1) * 12))) - Paye);

			setAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation + ((dyear + 1)* 12))));
			setResteAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation + ((dyear + 1) * 12))) - ((Paye/ ((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation + (dyear * 12))) * 100) *  (((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation + (dyear * 12))) / 100)));
			return ;
		}
		setAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100))  * (13 - monthDebitCreation)));
		setAnnuelleTtc(((PriceMonthTtc - RemiseMad) * (13 - monthDebitCreation)));
		setResteAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation)) - (Paye / ((PriceMonthTtc - RemiseMad)* (13 - monthDebitCreation)) * ((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation))  / 100 ));
		setResteAnnuelleTtc(((PriceMonthTtc - RemiseMad) * (13 - monthDebitCreation)) - Paye);
		setResteNew((((month + 1) - monthDebitCreation) * (PriceMonthTtc - RemiseMad)) - Paye);
		setTotalResteNew(((month + 1) - monthDebitCreation) * (PriceMonthTtc - RemiseMad));
	}
	////

	// function after choise company
		const Choisecompany =(e)=>{

			setId(e.id);
			setMessage({error : false, msg : ""});
			setsearch(e.Raisonsocial);	
			setHidelistsearch(true);
			setisSubDisable("");
			if (e.TVA !== undefined && Object.keys(e.TVA).length > 0 )
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
	const checkPayer =(nbr)=> {
		
		if (isNaN(nbr) || nbr === "" || /^\s*$/.test(nbr)) 
		{
			if (nbr === "") { 
				setPaye(0);
				setResteAnnuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100))* (13 - monthDebitCreation)));
				setResteAnnuelleTtc(((PriceMonthTtc - RemiseMad)* (13 - monthDebitCreation)));
				setResteMensuelleHt(PriceMonthHt - (RemisePercentage * PriceMonthHt/100) );
				setResteMensuelleTtc(PriceMonthTtc - RemiseMad);
				setResteNew((((month + 1) - monthDebitCreation) * (PriceMonthTtc - RemiseMad)));
			}
			return;
		}
		var e = parseInt(nbr);
		setPaye(e);
		setResteNew((((month + 1) - monthDebitCreation) * (PriceMonthTtc - RemiseMad)) - e);
		console.log(TotalResteNew);
		if (TotalResteNew - RemiseMad - e <= 0){
			setResteNew(0);
		}
		if (((PriceMonthTtc - RemiseMad)* (13 - monthDebitCreation) - e) <= 0)
		{
			setResteAnnuelleHt(0);
			setResteAnnuelleTtc(0);
		}
		setResteAnnuelleHt((((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation)) - (((e / ((PriceMonthTtc - RemiseMad )* (13 - monthDebitCreation)))* 100) * ((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) * (13 - monthDebitCreation)) / 100) ));
		setResteAnnuelleTtc(((PriceMonthTtc - RemiseMad)* (13 - monthDebitCreation) - e));
		if (PriceMonthTtc - (RemisePercentage * PriceMonthTtc/100) - e <= 0){
			setResteMensuelleHt(0);
			setResteMensuelleTtc(0);
			return ;
		}
		setResteMensuelleHt(((PriceMonthHt - (RemisePercentage * PriceMonthHt/100)) - (((e / (PriceMonthTtc - RemiseMad)) * 100) * PriceMonthHt / 100) ));
		setResteMensuelleTtc(PriceMonthTtc - RemiseMad - e);
	}
	////
	
	// check Remise en MAD
	const checkRemiseMad =(e)=> {
		if (isNaN(e) || e === "" || /^\s*$/.test(e)) 
		{
			if (e === "") { 
				setRemiseMad(0);
				setRemisePercentage(0);
				setResteMensuelleHt(PriceMonthHt);
				setResteMensuelleTtc(PriceMonthTtc);
				setResteNew((((month + 1) - monthDebitCreation) * PriceMonthTtc) - Paye);
				setResteAnnuelleTtc(((PriceMonthTtc - e)* (13 - monthDebitCreation)));
				setResteAnnuelleHt((((PriceMonthHt - 0) * (13 - monthDebitCreation))));
			}
			return;
		}
		var nbr = parseInt(e);
		var n = parseFloat((nbr / PriceMonthTtc) * 100) ;
		setResteAnnuelleHt(((
			(PriceMonthHt - n) * (13 - monthDebitCreation)) - (((Paye / ((PriceMonthTtc - nbr )* (13 - monthDebitCreation)))* 100) * ((PriceMonthHt - n) * (13 - monthDebitCreation)) / 100) ));
		setResteAnnuelleTtc(((PriceMonthTtc - nbr)* (13 - monthDebitCreation) - Paye));

		if (nbr <= PriceMonthTtc)
		{
			setResteMensuelleHt(0);
			setResteMensuelleTtc(0);
		}
		setRemiseMad(nbr);
		setRemisePercentage(n);
		setResteMensuelleHt((PriceMonthHt - (n * PriceMonthHt / 100) - Paye) ); 
		setResteMensuelleTtc(PriceMonthTtc - nbr - Paye);
		setResteNew((((month + 1) - monthDebitCreation) * (PriceMonthTtc - nbr) - Paye));
		return;
	}
	////

	// function check Remise on Percentage
	const checkRemisePercentage =(e)=> {
		if (isNaN(e) || e === "" || /^\s*$/.test(e)) 
		{
			if (e === "") { 
				setRemisePercentage(0); 
				setRemiseMad(0);
				setResteMensuelleHt(PriceMonthHt - Paye);
				setResteMensuelleTtc(PriceMonthTtc - Paye);
				setResteNew((((month + 1) - monthDebitCreation) * PriceMonthTtc) - Paye);
			}
	

			return;
		}
		var nbr = parseInt(e);
		if (nbr <= PriceMonthHt - (nbr / 100 * PriceMonthHt) - Paye)
		{
			setResteMensuelleHt(0);
			setResteMensuelleTtc(0);
		}
		setRemiseMad((PriceMonthTtc / 100) * nbr);
		setRemisePercentage(nbr);
		setResteMensuelleHt(PriceMonthHt - (nbr / 100 * PriceMonthHt) - Paye);
		setResteMensuelleTtc(PriceMonthTtc - (nbr / 100 * PriceMonthTtc) - Paye);
		setResteNew(((month + 1) - monthDebitCreation) * (PriceMonthTtc - (nbr / 100 * PriceMonthTtc) - Paye));
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

		setChiffreDaffaire(0);
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
			|| ChiffreDaffaire === 0 
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
				TVA.push (
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
		const NewTva = {
			TVA : {
				TVA,
				month,
				year,
				Paye,
				ChiffreDaffaire,
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
				await CompanyContext.updatecompany(Id, NewTva);
      	      	setMessage({error : false, msg : "Nouveau Declaration De TVA ajouté avec succès!" });
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
	    <h1 className=" text-center" >Declaration De TVA</h1>
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
                <label className="col-sm-4 col-form-label">Chiffre D’affaire</label>
                <div className="col-sm-8">
                  <input  type="text" 
                          className="form-control"
                          placeholder='0 Dh'
						  value={Number(ChiffreDaffaire.toFixed(2))}
						  onChange = {(e) => checkChiffreDaffaire(e.target.value)}
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
                          value={Number(PriceMonthHt.toFixed(2))}
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
                          value={Number(PriceMonthTtc.toFixed(2))}
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
                          value={Number(ResteMensuelleHt.toFixed(2))}
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
                          value={Number(ResteMensuelleTtc.toFixed(2))}
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
						  value={Number(ResteAnnuelleHt.toFixed(2))}
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
						  value={Number(ResteAnnuelleTtc.toFixed(2))}
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
                          value={Number(RemiseMad.toFixed(2))}
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
                          value={Number(RemisePercentage.toFixed(2))}
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
                          value={Number(Paye.toFixed(2))}
                          onChange = {(e) => checkPayer(e.target.value)}
                          />
                </div>
              </div>
            </div>
			<div className="col-md-6">
              <div className="form-group row">
                <label className="col-sm-4 col-form-label">Total Reste Actualite</label>
                <div className="col-sm-8">
                  <h3> {ResteNew.toFixed(2)} Dh</h3>
                </div>
              </div>
            </div>
			</div>
			
        </div>
                          
		<button type="submit" className = "btn button-right btn-scend btn-icon-text mr-2" ><i className="ti-file btn-icon-prepend"></i>Submit</button>
      </form>
      <div className="">
		<button className="btn button-right btn-inverse-dark mr-2" onClick={hideTva}>Cancel</button>
      </div>
      <Outlet/>
              </div>
          </div>
  )
}


export default NewTva;
