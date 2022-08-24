const fs = require('fs');
for (let i = 0; i < 1000000; i++) {

	let str = ''
	for (let j = 0; j < 30; j++) {
		str += String.fromCharCode(Math.floor(Math.random() * 26) + 97)
	}
	fs.appendFileSync("random.out", str + "\n")
}
