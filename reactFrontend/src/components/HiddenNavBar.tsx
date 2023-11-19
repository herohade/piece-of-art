import { Link } from "react-router-dom";
import "../css/NavBar.css";

type Props = {
  hidden: boolean;
};

// Navigation bar at the bottom of the page
function HiddenNavBar({ hidden }: Props) {
  return (
    <>
      {" "}
      <svg viewBox="0 0 24 19">
        {" "}
        <path
          fill="#ffffff"
          d="M24,17.5c0,0.8-0.7,1.5-1.6,1.5l-9.6,0H1.6C0.7,19,0,18.3,0,17.5v-0.1C0,16.7,0.7,16,1.6,16h20.7C23.3,16,24,16.6,24,17.5L24,17.5z"
        ></path>{" "}
        <path
          fill="#ffffff"
          d="M24,9.5c0,0.8-0.7,1.5-1.6,1.5H1.6C0.7,11,0,10.3,0,9.5V9.5C0,8.7,0.7,8,1.6,8h20.7C23.3,8,24,8.7,24,9.5L24,9.5z"
        ></path>{" "}
        <path
          fill="#ffffff"
          d="M24,1.5C24,2.3,23.3,3,22.4,3H1.6C0.7,3,0,2.4,0,1.6V1.5C0,0.7,0.7,0,1.6,0l9.6,0h11.1C23.3,0,24,0.7,24,1.5L24,1.5z"
        ></path>{" "}
      </svg>
      {!hidden && (
        <div className="hiddenHeaderNavigation">
          <nav>
            <ul>
              <li className="navListTop">
                <Link to={"/"}>Home</Link>
              </li>
              <li className="navListTop">
                <Link to={"/search"}>Find Craftsmen</Link>
              </li>
              <li className="navListTop">
                <Link to={"/update"}>Update Craftsmen</Link>
              </li>
            </ul>
          </nav>
        </div>
      )}
    </>
  );
}

export default HiddenNavBar;
