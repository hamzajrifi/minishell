import React, { useContext, useRef, useState } from "react";
import { UserContext } from "../../context/userContext";
import { useNavigate } from "react-router-dom";

export default function Login() {

    const { toggleModals, signIn } = useContext(UserContext);
    const navigate = useNavigate();
    const [Validation, setValidation] = useState("");

    const inputs = useRef([]);
    const addInputs = (el) => {
      if (el && !inputs.current.includes(el)) {
      inputs.current.push(el);
    } 
  };

  const formRef = useRef();
  const handleForm = async (e) => {
    e.preventDefault();
    // console.log(inputs);
    try {
        await signIn(
        inputs.current[0].value,
        inputs.current[1].value
      );
      //   formRef.current.reset();
      setValidation("");
      navigate("/");
      toggleModals("close");
    } catch {
        setValidation("E-mail ou mot de passe incorrect !");
    }
  };

  return (
	<>
      <div className=" top-0 v-100 vh-100 content-wrapper ">
        <div
          className="translate-middle-top-0-50 top-50 start-50
          translate-middle  align-items-center auth px-0"
        >
          <div className="auth-form-light m-auto "  style={{ maxWidth: "400px" }}>
            <div className="modal-content">
            <div className="auth-form-light text-left py-5 px-4 px-sm-5">
                    <div className="brand-logo  text-center">
                      <img src="images/logo-nav.png" alt="logo"/>
                    </div>
                    <h3 className="text-center ">Bounjour</h3>
                    <h4 className="text-center m-3">Connectez-vous pour continuer.</h4>
              <div className="">
                <form
                  ref={formRef}
                  onSubmit={handleForm}
                  className="sing-up-form pt-3"
                >
                  <div className="mb-3 form-group ">
                    <label htmlFor="signInEmail" className="form-label">
                      Email adress
                    </label>
                    <input
                      ref={addInputs}
                      name="email"
                      required
                      type="email"
                      className="form-control"
                      id="signInEmail"
                    />
                  </div>
                  <div className="mb-3">
                    <label htmlFor="signInPwd" className="form-label">
                      Password
                    </label>
                    <input
                      ref={addInputs}
                      name="pwd"
                      required
                      type="password"
                      className="form-control"
                      id="signInPwd"
                    />
                    <p className=" text-primary font-weight-medium mt-1">{Validation}</p>
                  </div>
                  <button className="btn btn-block btn-primary btn-lg font-weight-medium auth-form-btn " >Submit</button>
                </form>
              </div>
              </div>
            </div>
          </div>
        </div>
      </div>
  </>
  )
}
