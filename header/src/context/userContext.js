import { createContext, useState, useEffect } from "react";
import React from "react";
import {
  signInWithEmailAndPassword,
  createUserWithEmailAndPassword,
  onAuthStateChanged,
} from "firebase/auth";
import { auth } from "../firebase/firebase-config";
import { collection, getDocs, getDoc, addDoc, updateDoc, deleteDoc, doc} from "firebase/firestore";
import { db } from "../firebase/firebase-config";


// check if user true or not
export const UserContext = createContext();

export function UserContextProvider(props) {
  const signUp = (email, pwd) =>
    createUserWithEmailAndPassword(auth, email, pwd);
  const signIn = (email, pwd) => signInWithEmailAndPassword(auth, email, pwd);

  const [currentUser, setCurrentUser] = useState();
  const [loadingData, setLoadingData] = useState(true);

  useEffect(() => {
    const unsubscribe = onAuthStateChanged(auth, (currentUser) => {
      setCurrentUser(currentUser);
      setLoadingData(false);
    });
    return unsubscribe;
  }, []);

  //modal
  const [modalState, setModalState] = useState({
    signUpModal: false,
    signInModal: false,
  });
  const toggleModals = (modal) => {
    if (modal === "signIn") {
      setModalState({
        signUpModal: false,
        signInModal: true,
      });
    }

    if (modal === "signUp") {
      setModalState({
        signUpModal: true,
        signInModal: false,
      });
      console.log("here");
    }

    if (modal === "close") {
      setModalState({
        signUpModal: false,
        signInModal: false,
      });
    }
  };

  return (
    <UserContext.Provider
      value={{ modalState, toggleModals, signUp, currentUser, signIn }}
    >
      {!loadingData && props.children}
    </UserContext.Provider>
  );
}

// impote data user
const UserCollectionRef = collection(db, "users");

class DataUserContext   {
        addUsers = (newUser) => {
            if(!UserContext){return;}
            return addDoc(UserCollectionRef, newUser);
        };
    
        updateUser = (id, updateUser)=> {
            if(!UserContext){return;}
            const UserDoc = doc(db, "users", id);
            return updateDoc(UserDoc, updateUser);
        };
    
        deleteUser = (id) => {
            if(!UserContext){return;}
            const UserDoc = doc(db , "users", id);
            return deleteDoc (UserDoc);
        };
    
        getAllUsers = () => {
            // if(!UserContext){return;}
            return getDocs(UserCollectionRef);
        };
    
        getUser = (id) => {
            // if(!UserContext){return;}
            const UserDoc = doc (db, "users", id)
            return getDoc(UserDoc);
        }
    }
    export default new DataUserContext();
    