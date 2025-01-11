import { event, Events } from '../utils/index.js';
import file from "../commands/index.js";
import { ActivityType, REST, Routes } from 'discord.js';
import mongoose from 'mongoose';
import keys from '../keys.js';
const rest = new REST();
rest.setToken(process.env.CLIENT_TOKEN);

export default event(Events.ClientReady, async ({ log }, client) => {
    const arr: any[] = [];
    file.commands.forEach(v => {
        if(v.data){
            console.log(v);
            arr.push(v.data.toJSON());
        }
    })
    rest.put(Routes.applicationCommands(client.user.id, {
        commands: arr
    }));
    await mongoose.connect(keys.mongoURI)
    log("[DB]", "Running!");

    client.user.setPresence({ activities: [{ name: "c!help", type: ActivityType.Playing }] })
    return log("[Ready]", `logged in as ${client.user.username}`);
})