const alias = require("@rollup/plugin-alias");
const resolve = require("@rollup/plugin-node-resolve");


module.exports = {
    plugins: [
        alias({
            entries: [
                { find: "@com_nullcatalyst_prism/prism", replacement: "../external/com_nullcatalyst_prism/prism/js/index" },
            ],
        }),
        resolve(),
    ],
};
