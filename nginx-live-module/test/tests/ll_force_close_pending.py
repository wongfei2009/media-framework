from test_base import *

def updateConf(conf):
    block = getConfBlock(conf, ['live', 'preset ll'])
    block.append(['ll_segmenter_max_pending_segments', '1'])
    block.append(['ll_segmenter_frame_process_delay', '2s'])

# EXPECTED:
#   20 sec audio + video

def test(channelId=CHANNEL_ID):
    st = KmpSendTimestamps()

    nl = setupChannelTimeline(channelId, preset=LL_PRESET)

    rv = KmpMediaFileReader(TEST_VIDEO1, 0)
    ra = KmpMediaFileReader(TEST_VIDEO1, 1)

    sv, sa = createVariant(nl, 'var1', [('v1', 'video'), ('a1', 'audio')])

    kmpSendStreams([
        (rv, sv),
        (ra, sa),
    ], st, 20)

    kmpSendEndOfStream([sv, sa])

    nl.timeline.update(NginxLiveTimeline(id=TIMELINE_ID, end_list=True))

    time.sleep(5)

    testLLDefaultStreams(channelId, __file__)

    logTracker.assertContains('ngx_live_lls_force_close_segment: forcing close, started_tracks: 1')