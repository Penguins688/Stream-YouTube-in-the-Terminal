import yt_dlp
import subprocess
import os

video_url = input("Enter youtube url: ")
output_dir = 'video/'
output_template = os.path.join(output_dir, 'outVideo.%(ext)s')

ydl_opts = {
    'format': 'worst',
    'outtmpl': output_template,
}

os.makedirs(output_dir, exist_ok=True)

with yt_dlp.YoutubeDL(ydl_opts) as ydl:
    ydl.download([video_url])

actual_file = output_template.replace('%(ext)s', 'mp4')
with open("info.txt", "w") as info_file:
    info_file.write(f"{actual_file}")

subprocess.run(["executables/player"])