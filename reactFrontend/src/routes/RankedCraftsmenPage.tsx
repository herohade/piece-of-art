import { useParams } from "react-router-dom";
import Craftman from "../components/Craftman";
import Page from "../components/Page";

// Page for searching craftsmen by postcode
function RankedCraftsmenPage() {
  // get postcode from url: /craftsmen/search/:postcode
  const { postcode } = useParams();

  const sortedCraftsmanPlaceholder = [
    {
      id: 1,
      name: "Max Mustermann",
      rankingScore: 100,
    },
    {
      id: 2,
      name: "Frieda Musterfrau",
      rankingScore: 90,
    },
    {
      id: 3,
      name: "Anton Mustermann",
      rankingScore: 70,
    },
    {
      id: 4,
      name: "Lena Musterfrau",
      rankingScore: 70,
    },
    {
      id: 5,
      name: "Sebastian Mustermann",
      rankingScore: 50,
    },
  ];

  const content = (
    <>
      <h1>Ranked craftsmen for postcode {postcode}</h1>
      <ul>
        {sortedCraftsmanPlaceholder.map((craftsman) => (
          <li key={craftsman.id}>
            <Craftman
              id={craftsman.id}
              name={craftsman.name}
              rankingScore={craftsman.rankingScore}
            />
          </li>
        ))}
      </ul>
    </>
  );
  return <Page content={content} />;
}

export default RankedCraftsmenPage;
