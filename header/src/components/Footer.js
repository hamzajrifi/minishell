import React from 'react';
const Footer = () => {
    return (
            <footer className="footer">
                <div className="d-sm-flex justify-content-center justify-content-sm-between">
                  <span className="text-muted text-center text-sm-left d-block d-sm-inline-block">Copyright © 2022.  Premium <a href="https://www.marofiscal.ma/" >marofiscal admin Devloper</a> from marofiscal. All rights reserved.</span>
                  <span className="float-none float-sm-right d-block mt-1 mt-sm-0 text-center">Hand-crafted & made with <i className="ti-heart text-danger ml-1"></i></span>
                </div>
                <div className="d-sm-flex justify-content-center justify-content-sm-between">
                  <span className="text-muted text-center text-sm-left d-block d-sm-inline-block">Distributed by <a href="https://www.marofiscal.ma/" >maro_app</a></span> 
                </div>
            </footer> 
    )
};export default Footer;