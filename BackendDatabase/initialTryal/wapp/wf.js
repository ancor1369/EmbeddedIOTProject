var unirest = require("unirest");

var req = unirest("POST", "https://accuweatherstefan-skliarovv1.p.rapidapi.com/get24HoursConditionsByLocationKey");

req.headers({
	"x-rapidapi-host": "AccuWeatherstefan-skliarovV1.p.rapidapi.com",
	"x-rapidapi-key": "e28329f079mshab33f838910cc16p16b625jsnf8d17b1e7c30",
	"content-type": "application/x-www-form-urlencoded"
});

req.form({});