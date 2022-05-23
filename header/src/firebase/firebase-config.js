import { initializeApp } from "firebase/app";
import { getFirestore } from "@firebase/firestore";
import { getAuth } from "firebase/auth";


const firebaseConfig = {
  apiKey: "AIzaSyDaXUChfE1yRLwg-C5QDCk3nvyQNC-MtZE",
  authDomain: "test-b197d.firebaseapp.com",
  projectId: "test-b197d",
  storageBucket: "test-b197d.appspot.com",
  messagingSenderId: "392198803602",
  appId: "1:392198803602:web:e21556bb6f8a3d6c2a964b"
};


const app = initializeApp(firebaseConfig);

export const auth = getAuth(app);
export const db = getFirestore(app);