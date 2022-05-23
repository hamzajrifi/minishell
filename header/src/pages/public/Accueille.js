import React, { useEffect, useState } from 'react';
import { Route, Routes } from 'react-router-dom';
import Entreprises from '../../components/Client/Entreprises';
import NewClinet from '../../components/Client/NewClinet';
import Prospects from '../../components/Client/Prospects';
import CheckDeposit from "../../components/Etats declarations/CheckDeposit";
import Etatsdeclartion from '../../components/Etats declarations/Etatsdeclartion';
import Footer from '../../components/Footer';
import Navbar from "../../components/NavBar";
import Profile from '../../components/Profile';
import Sidebare from '../../components/Sidebare';
import TableauDeBord from '../../components/TableauDeBord';
import DataUserContext from '../../context/userContext';
import Bilan from '../../components/Traitement_Bilan/Bilan';
import PrintTva from '../../components/Print/PrintTva';
import Admin from "../Admin/Admin";
import Mombers from '../Admin/Mombers';
import Paiments from '../../components/Paiments/Paiments';

const Accueille = ({infoUser, AdminUid})=> {
  const [Users, SetUsers] = useState({});
  var datainfoUser = [Users, infoUser.uid, AdminUid];
  useEffect (() => {
		if( infoUser.uid !== undefined && infoUser.uid !== "")
    {
      const getdbUsers = async () => {
        const data = await DataUserContext.getUser(infoUser.uid);
        SetUsers(data.data());
      };
      getdbUsers(null);
    }
	},[infoUser.uid]);
  return (
    <div className=''>
      <div className="container-scroller">
          <Navbar infoUser={Users} Uid={infoUser.uid} AdminUid={AdminUid} />
          <div className="container-fluid page-body-wrapper">
            <Sidebare infoUser={Users} Uid={infoUser.uid} AdminUid={AdminUid} />
            <div className="content-wrapper">
              <Routes>
                <Route path="/" element={<TableauDeBord />}/>
                <Route path="/Profile" element={<Profile infoUser={Users}/>}/>
                <Route path="/Etatsdeclartion" element={<Etatsdeclartion />}/>
                <Route path="/Client" element={<NewClinet datainfoUser={datainfoUser} />}/>
                <Route path="/Entreprises" element={<Entreprises datainfoUser={datainfoUser} />}/>
                <Route path="/Prospects" element={<Prospects datainfoUser={datainfoUser} />}/>
                <Route path="/CheckDeposit" element ={<CheckDeposit />} />
                <Route path="/PrintTva" element={<PrintTva />}/>
                <Route path="/Bilan" element={<Bilan />}/>
                <Route path="/Paiments" element={<Paiments />}/>
                {!infoUser || (infoUser.uid !== AdminUid) ? 
                   <>
                    <Route path="/Mombers" element={<TableauDeBord />}/>
                    <Route path="/Admin" element={<TableauDeBord />}/>
                   </>
                : <>
                    <Route path="/Admin" element={<Admin />}/>
                    <Route path="/Mombers" element={<Mombers />}/>
                  </>
                }
              </Routes>
            </div>
          </div>
          <Footer  />
      </div>
    </div>
  )
}
export default Accueille; 