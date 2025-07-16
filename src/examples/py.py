import json

def generate_channel_entry(index):
    return {
        "url": f"http://stream{index}.example.com",
        "active": index % 2 == 0,
        "channelName": f"Channel {index}",
        "group": ["News", "Sports", "Entertainment", "Documentary"][index % 4],
        "tvg-ID": f"channel{index}.tvg",
        "tvg-logo": f"http://logo.example.com/{index}.png",
        "videoDecryptionKey": f"vdkey{index}",
        "audioDecryptionKey": f"adkey{index}",
        "videoQualities": ["2160p", "1080p", "720p"],
        "audioTracks": ["English", "French", "Spanish", "German"][index % 4:index % 4 + 2],
        "selectedVariants": {
            "video": "1080p",
            "audio": ["English"]
        }
    }

def generate_json_file(filename="channel_data.json", count=100):
    data = {
        "channelCount": count,
        "channels": {}
    }

    for i in range(1, count + 1):
        data["channels"][str(i)] = generate_channel_entry(i)

    with open(filename, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)
    print(f"✅ Successfully generated '{filename}' with {count} channels.")

generate_json_file()
