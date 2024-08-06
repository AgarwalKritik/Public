#   Author: KRITIK AGARWAL (https://github.com/Kritik007)
#   [Copyright (c) 2022 Kritik Agarwal](https://github.com/Kritik007/Airline-Fare-Prediction/blob/8ce82e4fec395c4acfc942d18471b7fe89b6bf8d/LICENSE#L3)

import datetime as dt
import pickle
import numpy as np
import pandas as pd
from flask import Flask, jsonify, render_template, request, url_for

app = Flask(__name__)

flight_model = pickle.load(open("AirlinePrice.pkl", "rb"))

airline_dict = {'Jet Airways': 4, 'IndiGo': 3, 'Air India': 1, 'Multiple carriers': 6, 'SpiceJet': 8,
                'Vistara': 10, 'Air Asia': 0, 'GoAir': 2, 'Multiple carriers Premium economy': 7,
                'Jet Airways Business': 5, 'Vistara Premium economy': 11, 'Trujet': 9}

sd_dict = {'Banglore': 0, 'Kolkata': 1, 'Delhi': 2,
           'Chennai': 3, 'Mumbai': 4, 'Cochin': 5, 'Hyderabad': 6}

total_stop_dict = {'non-stop': 0, '1 stop': 1,
                   '2 stops': 2, '3 stops': 3, '4 stops': 4}

Additional_Info_dict = {'No info': 7, 'In-flight meal not included': 5, 'No check-in baggage included': 6, '1 Long layover': 0,
                        'Change airports': 4, 'Business class': 3, '1 Short layover': 2, 'Red-eye flight': 1, '2 Long layover': 8}


# Load the model
@app.route('/')
def home():
    return render_template('index.html')


@app.route('/predict_api', methods=['POST'])
def predict_api():
    data = [x for x in request.form.values()]
    depart_time = data[0].split('T')[1]
    result = dt.datetime.strptime(
        data[1], '%H:%M')-dt.datetime.strptime(depart_time, '%H:%M')
    # print(result.seconds/60)

    if dt.datetime.strptime(depart_time, '%H:%M') == dt.datetime.strptime(data[1], '%H:%M'):
        duration_h = 24
        duration_min = 0
    else:
        duration_h = (result.seconds/60)//60
        duration_min = (result.seconds/60) % 60
    #print(duration_h, duration_min)

    filtered_data = []

    filtered_data.append(data[0].split('T')[0].split('-')[2])
    filtered_data.append(data[0].split('T')[0].split('-')[1])
    filtered_data.append(data[0].split('T')[1].split(':')[0])
    filtered_data.append(data[0].split('T')[1].split(':')[1])
    filtered_data.append(data[1].split(':')[0])
    filtered_data.append(data[1].split(':')[1])
    filtered_data.append(duration_h)
    filtered_data.append(duration_min)
    filtered_data.append(data[2])
    filtered_data.append(data[3])
    filtered_data.append(data[4])
    filtered_data.append(data[5])
    filtered_data.append(data[6])
    # print(filtered_data)

    filtered_data[8] = int(
        (pd.Series(filtered_data[8]).map(airline_dict)).values)
    filtered_data[9] = int((pd.Series(filtered_data[9]).map(sd_dict)).values)
    filtered_data[10] = int((pd.Series(filtered_data[10]).map(sd_dict)).values)
    filtered_data[11] = int(
        (pd.Series(filtered_data[11]).map(total_stop_dict)).values)
    filtered_data[12] = int(
        (pd.Series(filtered_data[12]).map(Additional_Info_dict)).values)

    filtered_data = [int(x) for x in filtered_data]
    final_input = np.array(filtered_data).reshape(1, -1)

    output = flight_model.predict(final_input)[0]
    print(output)

    return render_template('index.html', output_text="The Price of the flight journey is ₹{}/-".format(round(output, 2)))


if __name__ == '__main__':
    app.run(debug=True)
