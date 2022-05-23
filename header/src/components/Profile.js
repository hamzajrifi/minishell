import React from 'react'

export default function Profile({infoUser}) {
  return (
    <div className="col-md-4 grid-margin stretch-card"  style={{ minWidth: "400px" }}>
		<div className="card">
			<div className="card-body ">
				<div className="row m-auto text-center">
                    <div className="col-12 m-auto">
                        <img  src="images/user-image.png"  width="220px" height="220px" className=" rounded" alt="image_profile"/>
                    </div>
                    <div className="col-12 m-auto">
						<h6 className="">{infoUser.name}</h6>
						<p className="text-muted mb-1">{infoUser.email}</p>
						<p className="mb-0 text-success font-weight-bold">{infoUser.Profession}</p>
					</div>
				</div>
			</div>
		</div>
	</div>
  )
}
