import fs from 'fs'

function bin_search_i(arr: any[], target: any): number {
	let low = 0
	let high = arr.length - 1

	while (low <= high) {
		const mid = Math.floor((low + high) / 2)
		if (arr[mid] == target)
			return mid
		else if (arr[mid] < target)
			low = mid + 1
		else
			high = mid - 1
	}
	return -1
}

function measure(names: any[], find: any) {
	console.time('Search took')
	const index: number = bin_search_i(names, find)
	console.timeEnd('Search took')

	if (index < 0)
		console.log(`${find} not found`)
	else
		console.log(`Found ${find} at index ${index}`)
}

if (process.argv.length != 4) {
	console.log(`Usage: ${process.argv[0]} ${process.argv[1]} <input>`)
	process.exit(1)
}

const filename: string = process.argv[2]!
const find: string = process.argv[3]!
const names: string[] = fs.readFileSync(filename).toString().split('\n').sort()

console.log(`Searching for ${find} in array of ${names.length}...`)

for (let i = 0; i < 10; i++)
	measure(names, find)
