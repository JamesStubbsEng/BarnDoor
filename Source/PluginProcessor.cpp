/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BarnDoorAudioProcessor::BarnDoorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, Identifier("barndoor"),
                           {
                               //TODO: instantiate AudioParameterFloat parameters
                           })
#endif
{
}

BarnDoorAudioProcessor::~BarnDoorAudioProcessor()
{
}

//==============================================================================
const juce::String BarnDoorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BarnDoorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BarnDoorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BarnDoorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BarnDoorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BarnDoorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BarnDoorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BarnDoorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BarnDoorAudioProcessor::getProgramName (int index)
{
    return {};
}

void BarnDoorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BarnDoorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BarnDoorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BarnDoorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BarnDoorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    const auto numSamples = buffer.getNumSamples();

    if (numSamples == 0)
        return;
    auto playhead = getPlayHead();
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    if (playhead != nullptr)
    {
        playhead->getCurrentPosition(currentPositionInfo);
        isPlaying.store(currentPositionInfo.isPlaying);
    }

    //store to atomics that the PolarPlot will load
    //just capture first sample of buffer for now
    leftChannelSample.store(buffer.getSample(0, 0));
    if(buffer.getNumChannels() == 1)
        rightChannelSample.store(buffer.getSample(0, 0));
    else
        rightChannelSample.store(buffer.getSample(1, 0));
}

//==============================================================================
bool BarnDoorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BarnDoorAudioProcessor::createEditor()
{
    return new BarnDoorAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BarnDoorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void BarnDoorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

bool BarnDoorAudioProcessor::canGetLeftAndRightChannelSamples()
{
    return isPlaying.load();
}

void BarnDoorAudioProcessor::getLeftAndRightChannelSamples(float& l, float& r)
{
    l = leftChannelSample.load();
    r = rightChannelSample.load();
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BarnDoorAudioProcessor();
}
