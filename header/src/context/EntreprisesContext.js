import { db } from "../firebase/firebase-config";
import { collection, getDocs, getDoc, addDoc, updateDoc, deleteDoc, doc} from "firebase/firestore";

const cmpanyCollectionRef = collection(db, "Entreprises");
const prospectCollectionRef = collection(db, "prospects");

export  class CompanyContext {
	// client entreprises
	addCompaniens = (newCompany) => {
		return addDoc(cmpanyCollectionRef, newCompany);
	};

	updatecompany = (id, updatecompany)=> {
		const companyDoc = doc(db, "Entreprises", id);
		return updateDoc(companyDoc, updatecompany);
	};

	deletecompany = (id) => {
		const companyDoc = doc(db , "Entreprises", id);
		return deleteDoc (companyDoc);
	};

	getAllcompanies = () => {
		return getDocs(cmpanyCollectionRef);
	};

	getcompany = (id) => {
		const companyDoc = doc (db, "Entreprises", id)
		return getDoc(companyDoc);
	};
	// prospects 
	addPrpspects = (newProspect) => {
		return addDoc(prospectCollectionRef, newProspect);
	};

	updateProspect = (id, updateProspect)=> {
		const prospectDoc = doc(db, "prospects", id);
		return updateDoc(prospectDoc, updateProspect);
	};

	deleteprospect = (id) => {
		const prospectDoc = doc(db , "prospects", id);
		return deleteDoc (prospectDoc);
	};

	getAllprospects = () => {
		return getDocs(prospectCollectionRef);
	};

	getProspect = (id) => {
		const prospectDoc = doc (db, "prospects", id)
		return getDoc(prospectDoc);
	}
}
export default new CompanyContext();

