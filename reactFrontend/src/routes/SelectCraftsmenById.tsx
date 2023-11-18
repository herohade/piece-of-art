import { Form } from "react-router-dom";
import NavBar from "../components/NavBar";

// Page for searching the craftsman to update
function SelectCraftsmenById() {
  return (
    <>
      <h1>Search for the craftsman to update by id</h1>
      {/* input form asking for german postcode (5 digits) */}
      <Form method="post" id="craftsman-search-form" role="search">
        <label>
          <input type="number" name="craftsmanId" />
        </label>
        <button type="submit">Search</button>
      </Form>
      <NavBar />
    </>
  );
}

export default SelectCraftsmenById;