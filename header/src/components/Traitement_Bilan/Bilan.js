import React from 'react'
import Desimpots from './desimpots/Desimpots'

export default function Bilan() {
  return (
    <>
    {/*  */}
        <div  className="row">
            <div className="col-md-12 grid-margin grid-margin-md-0 stretch-card">
                <div className="card">
                    <div className="card-body">
                    <ul className="nav nav-pills mb-3" id="Bilan-tab" role="tablist">
                        <li className="nav-item">
                             <a className="nav-link active" id="Bilan-home-tab" data-toggle="pill" href="#Bilan-home" role="tab" aria-controls="Bilan-home" aria-selected="true">Bilan Des impots</a>
                        </li>
                        <li className="nav-item">
                              <a className="nav-link" id="Bilan-contact-tab" data-toggle="pill" href="#Bilan-contact" role="tab" aria-controls="Bilan-contact" aria-selected="false">Bilan Tribunaux</a>
                        </li>
                    </ul>
                    <div className="tab-content p-0" id="Bilan-tabContent">
                        <div className="tab-pane fade show active" id="Bilan-home" role="tabpanel" aria-labelledby="Bilan-home-tab">
                            <Desimpots />
                        </div>
                        <div className="tab-pane fade" id="Bilan-contact" role="tabpanel" aria-labelledby="Bilan-contact-tab">
                            {/* <Etats9421 />  */}
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    </>
    
)
}
