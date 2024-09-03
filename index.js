import React from 'react';

export default function Home({ data }) {
  return (
    <div style={{ padding: '20px', fontFamily: 'Arial, sans-serif' }}>
      <h1>Device Data</h1>
      <ul style={{ listStyleType: 'none', padding: 0 }}>
        {data.map((item) => (
          <li 
            key={item._id} 
            style={{ 
              marginBottom: '20px', 
              border: '1px solid #ccc', 
              padding: '10px', 
              borderRadius: '5px' 
            }}
          >
            <p><strong>Device:</strong> {item.device}</p>
            <p><strong>Value:</strong> {item.value}</p>
            <p><strong>Time:</strong> {new Date(item.time).toLocaleString()}</p>
          </li>
        ))}
      </ul>
    </div>
  );
}

export async function getServerSideProps() {
  
  const res = await fetch('http://192.168.1.73:3000/api/all-data');
  const data = await res.json();

  return {
    props: {
      data,
    },
  };
}
