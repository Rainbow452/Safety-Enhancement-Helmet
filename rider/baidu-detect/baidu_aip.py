
from aip import AipSpeech
flag=0
def Speech_To_Text(filePath):  # 百度语音识别
	""" 你的 APPID AK SK """
	APP_ID = '26187663'
	API_KEY = '4Hq1paejINtUGnXA6h2joCIs'
	SECRET_KEY = 'IP95lKAgn2u5d8kv9zm9OBu0wzVGPvUj'
	aipSpeech = AipSpeech(APP_ID, API_KEY, SECRET_KEY)  # 初始化AipSpeech对象
	# 读取文件
	with open(filePath, 'rb') as fp:
		audioPcm = fp.read()
	json = aipSpeech.asr(audioPcm, 'wav', 16000, {'lan': 'zh', })
	print(json)
	if 'success' in json['err_msg']:
		context = json['result'][0]
		
		print('成功，返回结果为：', context)
		
		#if '北京' in context:


	else:
		context = '=====识别失败====='
		print('识别失败！')
		return context
	with open('baidu_aip_result.txt',"w") as f:
		f.truncate(0)
		if "录视频" in context:
			f.write("{}\n".format("video"))
		else:
			f.write("{}\n".format("no"))
		if "拍照" in context:
			f.write("{}\n".format("photo")) 
		else:
			f.write("{}\n".format("no")) 
# oldPath='./audio/韩红 - 家乡.mp3'
#oldPath = './audio/16k.wav'
# oldPath='temp-1.wav'
oldPath='audio/3.wav'


Speech_To_Text(oldPath)
