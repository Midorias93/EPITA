const axios = require('axios');

async function notSoFast(host, port) {
    const baseURL = `http://${host}:${port}`;
    let articles = [];

    try {

        const totalCountResponse = await axios.get(`${baseURL}/articles`);
        let totalCount = totalCountResponse.data.message;

        let id = 0;



        while (id < totalCount) {
            try {
                let articleResponse = await axios.get(`${baseURL}/articles/${id}`);
                articles.push(articleResponse.data);
                id++;
                if (Number(articleResponse.headers['x-ratelimit-remaining']) === 0) {
                    await new Promise(resolve => setTimeout(resolve, Number(articleResponse.headers['x-ratelimit-reset'] * 1000 - Date.now())));

                }
            }
            catch (error) {
                if (error.response && error.response.status === 429) {
                    console.error('Rate limit hit, delaying further requests');
                } else {
                    console.error('Failed to fetch article:', error.message);
                }
            }
        }

    }
    catch (error) {
        console.error('Failed to fetch total count:', error.message); }
    return articles;
}

(async () => {
    const startTime = Date.now();
    const articlesList = await notSoFast("localhost", 3000);
    const endTime = Date.now();
    console.log("elapsed:", endTime - startTime, "ms")
    console.log("length:", articlesList.length);
}
)();

module.exports = { notSoFast }; 