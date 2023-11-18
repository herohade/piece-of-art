type Props = {
  id: number;
  name?: string;
  rankingScore?: number;
};

// Navigation bar at the bottom of the page
function Craftman({ id, name, rankingScore }: Props) {
  return <>
    <div className="craftman">
      <h2>{name && name+" "}({id})</h2>
      {rankingScore && <p>Ranking score: {rankingScore} / 100</p>}
    </div>
  </>;
}

export default Craftman;
