const axios = require('axios').default;

const sendRequest = async (options) => {
    try {
        const { data } = await axios(options);
        return data;
    } catch (error) {

        throw error;
    }
}

module.exports = {
    sendRequest
}