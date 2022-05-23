import React from 'react'
import AddMomber from './AddMomber'

export function ListMombers() {
  return (
    <>
        <div className="col-md-7 d-none grid-margin grid-margin-md-0 stretch-card">
							<div className="card">
								<div className="card-body">
									<h4 className="card-title">hamza</h4>
									<div className="table-responsive">
                    <table className="table">
                      <thead>
                        <tr>
                          <th className="pt-1 ps-0">
                            Assigned
                          </th>
                          <th className="pt-1">
                            Product
                          </th>
                          <th className="pt-1">
                            Priority
                          </th>
                        </tr>
                      </thead>
                      <tbody>
                        <tr>
                          <td className="py-1 ps-0">
                            <div className="d-flex align-items-center">
                              <img src="../../../../images/faces/face1.jpg" alt="profile"/>
                              <div className="ms-3">
                                <p className="mb-0">Sophia Brown</p>
                                <p className="mb-0 text-muted text-small">Product Designer</p>
                              </div>
                            </div>
                          </td>
                          <td>
                            Web App
                          </td>
                          <td>
                            <label className="badge badge-success">Low</label>
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
		    	</div>
	    	</div>
	    </div>
    </>
  )
}

export default function Mombers() {
  return (
    <div className='row'>
        <ListMombers />
        <AddMomber />
    </div>
  )
}
