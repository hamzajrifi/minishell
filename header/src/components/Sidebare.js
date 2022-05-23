import React from 'react'
import { Link } from 'react-router-dom'
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {	faBuilding, faBuildingCircleCheck, faBuildingCircleExclamation, faCommentDots, faFileSignature, faUserGroup
} from "@fortawesome/free-solid-svg-icons";

const Sidebare =({infoUser, Uid, AdminUid})=> {
  return (
    <>
    <nav className="sidebar sidebar-offcanvas" id="sidebar">
    <ul className="nav">
      <li className="nav-item">
        <Link className="nav-link" to="/">
          <i className="icon-grid menu-icon"></i>
          <span className="menu-title">Tableau De Bord</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="/Etatsdeclartion">
            <i  className="ti-bar-chart menu-icon"></i>
          <span className="menu-title">États Déclaration</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="/Client">
          <i className="icon-head menu-icon"></i>
          <span className="menu-title">Clients</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="/">
        <i  className="ti-calendar menu-icon"></i>
          <span className="menu-title">Rendez-vous</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="/">
          <FontAwesomeIcon icon = {faCommentDots} className =' icon-font-menu'/>
          <span className="menu-title">Messages</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="/Bilan">
          <FontAwesomeIcon icon = {faFileSignature} className =' icon-font-menu'/>
          <span className="menu-title">Traitement Bilan</span>
        </Link>
      </li>
	  	<li className="nav-item">
        	<a className="nav-link" data-toggle="collapse" href="#ui-basic" aria-expanded="false" aria-controls="ui-basic">
				<FontAwesomeIcon icon = {faBuilding} className =' icon-font-menu '/>
				<span className="menu-title">Entreprises</span>
        	  <i className="menu-arrow"></i>
        	</a>
        	<div className="collapse" id="ui-basic">
        	 	<ul className="nav flex-column sub-menu pl-3 pt-0 pb-0">
				 	<li className="border-bottom">
						<Link className="nav-link text-white pl-3 pt-0 pb-0" to="/Entreprises">
							<FontAwesomeIcon icon = {faBuildingCircleCheck} className ='text-white icon-font-menu '/>
							Entreprises
						</Link>
					</li>
        				<li className="">
					   <Link className="nav-link text-white pl-3" to="/Prospects">
							<FontAwesomeIcon icon = {faBuildingCircleExclamation} className ='text-white icon-font-menu'/>
						   	Prospects
						</Link>
					</li>
        	  	</ul>
        	</div>
        </li>
      <li className="nav-item">
        <Link className="nav-link" to="pages/documentation/documentation.html">
          <i className="icon-paper menu-icon"></i>
          <span className="menu-title">Devis</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="PrintTva">
          <i className="icon-paper menu-icon"></i>
          <span className="menu-title">Factures</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="pages/documentation/documentation.html">
        <i  className="ti-menu-alt menu-icon"></i>
          <span className="menu-title">Services</span>
        </Link>
      </li>
      <li className="nav-item">
        <Link className="nav-link" to="/Paiments">
          <i className="icon-paper menu-icon"></i>
          <span className="menu-title">Paiments</span>
        </Link>
      </li>
      {!infoUser || (Uid !== AdminUid) ? null :
      <>
      <li className="nav-item">
        <Link className="nav-link" to="/Mombers">
          <FontAwesomeIcon icon={faUserGroup} className=" icon-font-menu"/>
          <span className="menu-title">Membres</span>
        </Link>
      </li>
        <li className="nav-item">
          <Link className="nav-link" to="/Admin">
          <i  className="ti-settings menu-icon"></i>
            <span className="menu-title">Paramètres</span>
          </Link>
        </li>
      </>
      }
    </ul>
    
  </nav>
  </>
  )
}
export default Sidebare;