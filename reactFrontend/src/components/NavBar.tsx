import { Link } from "react-router-dom";
import "../css/NavBar.css";

// Navigation bar at the bottom of the page
function NavBar() {
  return (
    <>
      <footer className="footer">
        <nav>
          <ul>
            <li className="navListBottom">
              <Link to={"/"}>Home</Link>
            </li>
            <li className="navListBottom">
              <Link to={"/craftsmen/search"}>Find Craftsmen</Link>
            </li>
            <li className="navListBottom">
              <Link to={"/craftsmen/update"}>Update Craftsmen</Link>
            </li>
          </ul>
        </nav>
      </footer>
    </>
  );
}

export default NavBar;
