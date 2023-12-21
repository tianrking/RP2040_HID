addEventListener('fetch', event => {
  event.respondWith(handleRequest(event.request))
})

async function handleRequest(request) {
  const path = new URL(request.url).pathname;
  
  if (path === "/draw") {
    return new Response(html(), {
      headers: { 'Content-Type': 'text/html' },
    });
  }

  if (path === "/raw") {
    return new Response(html_raw(), {
      headers: { 'Content-Type': 'text/html' },
    });
  }

  return new Response("Not Found", { status: 404 });
}

function html() {
  return `<!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Mouse Draw</title>
      <style>
          canvas {
              border: 1px solid black;
          }
      </style>
  </head>
  <body>
      <canvas id="mouseCanvas" width="800" height="600"></canvas>
      <script>
          const canvas = document.getElementById('mouseCanvas');
          const ctx = canvas.getContext('2d');
          let isDrawing = false;

          canvas.onmousedown = (e) => {
              isDrawing = true;
              ctx.moveTo(e.offsetX, e.offsetY);
          };

          canvas.onmousemove = (e) => {
              if (isDrawing) {
                  ctx.lineTo(e.offsetX, e.offsetY);
                  ctx.stroke();
              }
          };

          canvas.onmouseup = () => {
              isDrawing = false;
          };

          canvas.onmouseout = () => {
              isDrawing = false;
          };
      </script>
  </body>
  </html>`;
}

function html_raw() {
  return `<!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Mouse Draw</title>
      <style>
          canvas {
              border: 1px solid black;
              position: absolute;
              top: 0;
              left: 0;
          }
          #countdown {
              position: fixed;
              top: 50%;
              left: 50%;
              transform: translate(-50%, -50%);
              font-size: 100px;
              color: #90EE90;
              opacity: 1;
              transition: opacity 0.5s ease, font-size 0.5s ease;
          }
      </style>
  </head>
  <body>
      <div id="countdown"></div>
      <canvas id="mouseCanvas"></canvas>
      <script>
          const countdownElement = document.getElementById('countdown');
          let countdown = 3;
          countdownElement.innerText = countdown;
          countdownElement.style.fontSize = '100px';
          countdownElement.style.opacity = '1';

          const countdownInterval = setInterval(() => {
              countdown -= 1;
              countdownElement.innerText = countdown;
              countdownElement.style.fontSize = '150px';
              countdownElement.style.opacity = '0';
              if (countdown <= 0) {
                  clearInterval(countdownInterval);
                  countdownElement.style.display = 'none';
                  enableDrawing();
              } else {
                  setTimeout(() => {
                      countdownElement.style.fontSize = '100px';
                      countdownElement.style.opacity = '1';
                  }, 500);
              }
          }, 1000);

          const canvas = document.getElementById('mouseCanvas');
          canvas.width = window.innerWidth;
          canvas.height = window.innerHeight;
          const ctx = canvas.getContext('2d');
          let points = [];
          let lastColor = randomColor();
          let isDrawingEnabled = false;

          function enableDrawing() {
              isDrawingEnabled = true;
              canvas.onmousemove = (e) => {
                  if (!isDrawingEnabled) return;
                  points.push({ x: e.offsetX, y: e.offsetY, color: lastColor });
                  lastColor = randomColor();
                  redraw();
              };
          }

          function redraw() {
              ctx.clearRect(0, 0, canvas.width, canvas.height);
              ctx.beginPath();
              points.forEach((point, index) => {
                  ctx.strokeStyle = point.color;
                  ctx.lineTo(point.x, point.y);
                  ctx.stroke();
                  ctx.beginPath();
                  ctx.moveTo(point.x, point.y);
              });
          }

          function randomColor() {
              const r = Math.floor(Math.random() * 256);
              const g = Math.floor(Math.random() * 256);
              const b = Math.floor(Math.random() * 256);
              return \`rgb(\${r}, \${g}, \${b})\`;
          }
      </script>
  </body>
  </html>`;
}
