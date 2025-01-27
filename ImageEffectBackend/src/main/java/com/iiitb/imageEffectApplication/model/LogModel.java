package com.iiitb.imageEffectApplication.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class LogModel {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;
    private String timestamp; // The time at which the effect was applied
    private String filename; // The name of the file on which the effect is applied
    private String effectName; // The name of the effect applied
    private String optionValues; // The comma-separated list of option-value pairs

    public LogModel() {

    }

    public LogModel(String timestamp, String filename, String effectName, String optionValues) {
        this.timestamp = timestamp;
        this.filename = filename;
        this.effectName = effectName;
        this.optionValues = optionValues;
    }

    public String getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(String timestamp) {
        this.timestamp = timestamp;
    }

    public String getFilename() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public String getEffectName() {
        return effectName;
    }

    public void setEffectName(String effectName) {
        this.effectName = effectName;
    }

    public String getOptionValues() {
        return optionValues;
    }

    public void setOptionValues(String optionValues) {
        this.optionValues = optionValues;
    }

    @Override
    public String toString()
    {
        System.out.println(this.filename);
        System.out.println(this.effectName);
        System.out.println(this.timestamp);
        System.out.println(this.optionValues);
        return "";
    }
}
