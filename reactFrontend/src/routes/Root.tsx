import { useState } from "react";

import Page from "../components/Page";

import "../css/Root.css";

// The root of the website
// TODO: pretty up
function Root() {
  const [count, setCount] = useState(100);

  const content = (
    <div className="contentBody">
      <div className="rotate">Rest in Peace</div>
      <h1>We are fucked</h1>
      <div className="card">
        <button onClick={() => setCount((count) => count + 1)}>
          {count} people agree
        </button>
      </div>
    </div>
  );

  return <Page content={content} />;
}

export default Root;
