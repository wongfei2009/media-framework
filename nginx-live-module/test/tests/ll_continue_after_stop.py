from test_base import *

# EXPECTED:
#   continuous 40 sec audio + video

def updateConf(conf):
    block = getConfBlock(conf, ['live', 'preset ll'])
    block.append(['ll_segmenter_inactive_timeout', '100s'])
    block.append(['persist_bucket_size', '1'])

def stream(nl, duration, eos):
    rv = KmpMediaFileReader(TEST_VIDEO1, 0)
    ra = KmpMediaFileReader(TEST_VIDEO1, 1)
    st = KmpSendTimestamps()

    sv, sa = createVariant(nl, 'var1', [('v1', 'video'), ('a1', 'audio')], flags=KMP_CONNECT_FLAG_CONSISTENT)

    kmpSendStreams([
        (rv, sv),
        (ra, sa),
    ], st, duration)

    if eos:
        kmpSendEndOfStream([sv, sa])
    else:
        time.sleep(2)
        sv.close()
        sa.close()

def setup(channelId=CHANNEL_ID):
    nl = setupChannelTimeline(channelId, preset=LL_PRESET)

    nl.channel.update(NginxLiveChannel(id=channelId, segment_duration=8000))

    stream(nl, 20, False)

def test(channelId=CHANNEL_ID):
    nl = nginxLiveClient()
    nl.channel.create(NginxLiveChannel(id=channelId, preset=LL_PRESET))
    nl.setChannelId(channelId)

    stream(nl, 30, False)
    stream(nl, 40, True)

    time.sleep(2)
    nl.timeline.update(NginxLiveTimeline(id=TIMELINE_ID, end_list=True))

    testLLDefaultStreams(channelId, __file__)