import { useState } from "react";
import "../css/NavBar.css";
import HiddenNavBar from "./HiddenNavBar";
import { Link } from "react-router-dom";

// Navigation bar at the bottom of the page
function HeaderBar() {
  const [hiddenNav, setHiddenNav] = useState(true);
  return (
    <>
      <header>
        <div className="headerTop">
          <Link to="/">
            <div className="headerLogo"></div>
          </Link>
          <div className="headerNavigation">
            <HiddenNavBar hidden={hiddenNav} />
            <button
              className="headerNavButton"
              onClick={() => {
                setHiddenNav(!hiddenNav);
                console.log(hiddenNav);
              }}
            ></button>
          </div>
        </div>
      </header>
    </>
  );
}

export default HeaderBar;
