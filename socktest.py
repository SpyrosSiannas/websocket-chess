#/usr/env/bin python3

import websockets

async def sock():
    async with websockets.connect("ws://127.0.0.1:9001/") as websocket:
        await websocket.send("create Hello, World!")
        response  = await websocket.recv()
        sessionID = int(response)
        print(f"Created session {sessionID}")
        res = await websocket.send(f"join {sessionID}")
        res = await websocket.recv()
        print(res)
import asyncio 

if __name__ == "__main__":
    asyncio.run(sock())
