import { Form } from "react-router-dom";
import Page from "../components/Page";

// Page for searching craftsmen by postcode
function SearchCraftsmenByPostcodePage() {
  const content = (
    <>
      <h1>Search for craftsmen by postcode</h1>
      {/* input form asking for german postcode (5 digits) */}
      <Form method="post" id="postcode-search-form">
        <label>
          <input type="number" name="postcode" />
        </label>
        <button type="submit">Search</button>
      </Form>
    </>
  );
  return (<Page content={content} />
  );
}

export default SearchCraftsmenByPostcodePage;
