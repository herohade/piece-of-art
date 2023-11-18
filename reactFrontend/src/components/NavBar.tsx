import { Link } from "react-router-dom";
import "../css/NavBar.css";

// Navigation bar at the bottom of the page
function NavBar() {
  return (
    <>
      <nav>
        <ul>
          <li className="navList">
            <Link to={"/"}>Home</Link>
          </li>
          <li className="navList">
            <Link to={"/craftsmen/search"}>Find Craftsmen</Link>
          </li>
          <li className="navList">
            <Link to={"/craftsmen/update"}>Update Craftsmen</Link>
          </li>
        </ul>
      </nav>
    </>
  );
}

export default NavBar;
