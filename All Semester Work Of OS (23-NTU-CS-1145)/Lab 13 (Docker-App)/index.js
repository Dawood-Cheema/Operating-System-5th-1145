import express from 'express'
const app = express()

app.use(express.static('public'))
function handler (req, res) {
  res.sendFile('/index.html');
}

app.get('/', handler)
app.listen(3000)