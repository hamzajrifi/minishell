import Login from "./pages/Login/Login";
import {UserContext }from "./context/userContext"
import React, { useContext } from "react";
import Accueille from "./pages/public/Accueille";

function App() {
  const { currentUser } = useContext(UserContext);
  const AdminUid = "Yp9LmGaC0AZxbvH3cgggPkyDi482";
  return (
    <>
       { currentUser ? <Accueille infoUser={currentUser} AdminUid={AdminUid} /> : <Login />}
    </>
  );
}
export default App;