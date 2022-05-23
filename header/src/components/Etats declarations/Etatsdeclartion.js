import React from 'react';
import Cnss from './Cnss/Cnss';
import Etats9421 from './Etats_9421/Etats9421';
import DeclarationTva from './Tva/Tva';

const Etatsdeclartion =() => {
return (
    <>
		{/*  */}
			<div  className="row">
				<div className="col-md-12 grid-margin grid-margin-md-0 stretch-card">
					<div className="card">
						<div className="card-body">
						<ul className="nav nav-pills mb-3" id="pills-tab" role="tablist">
							<li className="nav-item">
							 	<a className="nav-link active" id="pills-home-tab" data-toggle="pill" href="#pills-home" role="tab" aria-controls="pills-home" aria-selected="true">TVA</a>
							</li>
							<li className="nav-item">
							  	<a className="nav-link" id="pills-contact-tab" data-toggle="pill" href="#pills-contact" role="tab" aria-controls="pills-contact" aria-selected="false">ETAT 9421</a>
							</li>
							<li className="nav-item">
							  	<a className="nav-link" id="pills-profile-tab" data-toggle="pill" href="#pills-profile" role="tab" aria-controls="pills-profile" aria-selected="false">CNSS</a>
							</li>
						</ul>
						<div className="tab-content p-0" id="pills-tabContent">
							<div className="tab-pane fade show active" id="pills-home" role="tabpanel" aria-labelledby="pills-home-tab">
								<DeclarationTva />
							</div>
							<div className="tab-pane fade" id="pills-contact" role="tabpanel" aria-labelledby="pills-contact-tab">
								<Etats9421 /> 
							</div>
							<div className="tab-pane fade" id="pills-profile" role="tabpanel" aria-labelledby="pills-profile-tab">
								<Cnss />
								</div>
						</div>
					</div>
				</div>
			</div>
		</div>
		</>
		
  )
}
export default Etatsdeclartion;