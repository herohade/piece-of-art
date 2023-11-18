import { useState } from 'react'
import '../css/Root.css'

function Root() {
  const [count, setCount] = useState(100)

  return (
    <>
      <div className='rotate'>
        Rest in Peace
      </div>
      <h1>We are fucked</h1>
      <div className="card">
        <button onClick={() => setCount((count) => count + 1)}>
          {count} people agree
        </button>
      </div>
    </>
  )
}

export default Root
