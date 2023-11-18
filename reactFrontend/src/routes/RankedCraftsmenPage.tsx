import { useParams } from "react-router-dom";
import NavBar from "../components/NavBar";

// Page for searching craftsmen by postcode
function RankedCraftsmenPage() {
  // get postcode from url: /craftsmen/search/:postcode
  const { postcode } = useParams();
  return (
    <>
      <h1>Ranked craftsmen for postcode {postcode}</h1>
      <ul>
        <li>1. Max Mustermann</li>
        <li>2. Max Mustermann</li>
        <li>3. Max Mustermann</li>
        <li>4. Max Mustermann</li>
        <li>5. Max Mustermann</li>
      </ul>
      <NavBar />
    </>
  );
}

export default RankedCraftsmenPage;