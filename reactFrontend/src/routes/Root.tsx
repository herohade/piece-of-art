import { useState } from "react";
import NavBar from "../components/NavBar";

import "../css/Root.css";

// The root of the website
// TODO: pretty up
function Root() {
  const [count, setCount] = useState(100);

  return (
    <>
      <div className="rotate">Rest in Peace</div>
      <h1>We are fucked</h1>
      <div className="card">
        <button onClick={() => setCount((count) => count + 1)}>
          {count} people agree
        </button>
      </div>
      <NavBar />
    </>
  );
}

export default Root;
