import { Form } from "react-router-dom";
import NavBar from "../components/NavBar";

// Page for searching craftsmen by postcode
function SearchCraftsmenPage() {
  return (
    <>
      <h1>Search for craftsmen by postcode</h1>
      {/* input form asking for german postcode (5 digits) */}
      <Form method="post" id="postcode-search-form" role="search">
        <label>
          <input type="number" name="postcode" />
        </label>
        <button type="submit">Search</button>
      </Form>
      <NavBar />
    </>
  );
}

export default SearchCraftsmenPage;
