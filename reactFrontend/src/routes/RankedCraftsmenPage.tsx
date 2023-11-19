import { Form, useLocation, useParams } from "react-router-dom";
import Craftman from "../components/Craftman";
import Page from "../components/Page";
import { useEffect, useState } from "react";
import { getCraftsmenByPostalCode } from "../functions/openApiWrapper";
import { Craftsman, Response } from "../services/openapi";

// Page for searching craftsmen by postcode
function RankedCraftsmenPage() {
  // get postcode from url: /search/:postcode
  const { postcode } = useParams();

  if (!postcode) {
    throw new Error("No postcode provided");
  }

  const { search } = useLocation();
  const params = new URLSearchParams(search);
  const { count } = Object.fromEntries(params);
  const numEntries = isNaN(Number(count)) ? 20 : Number(count);

  const [sortedCraftsman, setSortedCraftsman] = useState([] as Craftsman[]);
  useEffect(() => {
    getCraftsmenByPostalCode(postcode, numEntries).then(
      (response: Response | undefined) => {
        if (!response) {
          if (import.meta.env.DEV) {
            console.log("undefined response");
          }
          return;
        }
        const { craftsmen } = response;
        setSortedCraftsman(craftsmen || []);
      }
    );
  }, [postcode, numEntries]);

  const content = (
    <div className="contentBody">
      <h1>Ranked craftsmen for postcode {postcode}</h1>
      <ul>
        {sortedCraftsman !== undefined &&
          sortedCraftsman.map((craftsman) => (
            <li key={craftsman.id}>
              <Craftman
                id={craftsman.id || 0}
                name={craftsman.name || ""}
                rankingScore={craftsman.rankingScore || 0}
              />
            </li>
          ))}
      </ul>
      <Form method="post" id="load-more-form">
        <button type="submit">Load More</button>
      </Form>
    </div>
  );
  return <Page content={content} />;
}

export default RankedCraftsmenPage;
