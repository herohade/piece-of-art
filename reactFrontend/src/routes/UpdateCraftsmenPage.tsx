import { useParams } from "react-router-dom";
import NavBar from "../components/NavBar";

// Page for searching craftsmen by postcode
function UpdateCraftsmenPage() {
  // get id from url: /craftsmen/update/:id
  const { id } = useParams();
  return (
    <>
      <h1>Update this Craftsman {id}</h1>
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

export default UpdateCraftsmenPage;